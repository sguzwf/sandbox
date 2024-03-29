module DeriveTemplate where

import Data.Functor
import Data.List
import Data.Char
import Data.Monoid
import Data.String
import Control.Applicative
import Control.Monad
import qualified Data.Set as S
import qualified Data.Map as M
import Language.Haskell.TH
import Language.Haskell.TH.Syntax
import Language.Haskell.TH.Ppr
import Language.Haskell.TH.Quote

data CodeAtom
  = StaticCode String
  | VarCode String
  deriving Show

newtype CodeGen = CodeGen [CodeAtom] deriving (Monoid, Show)

varCode :: String -> CodeGen
varCode name = CodeGen [VarCode name]

staticCode :: String -> CodeGen
staticCode str = CodeGen [StaticCode str]

intercalateCode :: CodeGen -> [CodeGen] -> CodeGen
intercalateCode sep = go where
  go [] = CodeGen []
  go [atom] = atom
  go (a : as) = a <> sep <> go as

genCode :: CodeGen -> Q Exp
genCode (CodeGen codeAtoms) = varE (mkName "mconcat") `appE` listE (map codeAtomToExp (unionStatic codeAtoms)) where 

  unionStatic (a : as) =
    case (a, unionStatic as) of
      (StaticCode aStr, StaticCode asStr : others) -> StaticCode (aStr <> asStr) : others
      (_, as') -> a : as'
  unionStatic _ = []

  codeAtomToExp (StaticCode str) = stringE str
  codeAtomToExp (VarCode name) = varE (mkName name)

instance IsString CodeAtom where
  fromString = StaticCode

instance IsString CodeGen where
  fromString = CodeGen . pure . fromString

trivialTypes :: S.Set String
trivialTypes = S.fromList ["String", "Maybe", "Int", "Rational", "Char", "Integer", "Bool"]

reservedNames :: S.Set String
reservedNames = S.fromList ["type", "deriving"]

deriveDesugarTemplate :: String -> String -> Bool -> Q [Dec]
deriveDesugarTemplate funName moduleNameStr mode = do
  Just moduleName <- lookupTypeName moduleNameStr

  moduleInfo <- reify moduleName
  --runIO $ putStrLn $ show moduleInfo

  allComponent <- collectAllNonTrivialComponent moduleName
  --runIO $ putStrLn (show allComponent)

  allCode <- forM (S.toList allComponent) $ \name -> do
    info <- reify name
    let code = genDataTransformer info
    --runIO $ putStrLn code
    return code
  let
    importSyntax = if mode then "import Language.Haskell.Exts.Annotated.Syntax" else "import Language.Haskell.Exts.Syntax"
    generatedExp = genCode $ mconcat $ CodeGen [StaticCode "module ", VarCode "modName", StaticCode " where\n", StaticCode importSyntax, StaticCode "\nimport Control.Arrow ((***))\n"] : allCode
  --ee <- generatedExp
  --runIO $ putStrLn $ pprint ee
  --runIO $ putStrLn $ show allCode
  --
    generatedFunDQ = funD (mkName funName)
      [ clause (map (varP . mkName) ["modName", "funPrefix", "additionalArgNum"])
        (normalB generatedExp)
--        [ [d| additionalArgsType = concat $ map (\i -> 'a' : show i ++ " ->") [1 .. additionalArgNum] |]
--        , [d| additionalArgsExp = concat $ map (\i -> " a" ++ show i) [1 .. additionalArgNum] |]
--        ]
        [ valD
          (varP (mkName "additionalArgsType"))
          (normalB (varE (mkName "concat") `appE` (varE (mkName "map") `appE` lam1E (varP (mkName "i")) (infixApp (litE (charL 'a')) (conE (mkName ":")) (infixApp (varE (mkName "show") `appE` varE (mkName "i")) (varE (mkName "++")) (stringE " -> "))) `appE` arithSeqE (litE (integerL 1) `fromToR` varE (mkName "additionalArgNum")))))
          []
        , valD
          (varP (mkName "additionalArgsExp"))
          (normalB (varE (mkName "concat") `appE` (varE (mkName "map") `appE` lam1E (varP (mkName "i")) (infixApp (stringE " a") (varE (mkName "++")) (varE (mkName "show") `appE` varE (mkName "i"))) `appE` arithSeqE (litE (integerL 1) `fromToR` varE (mkName "additionalArgNum")))))
          []
        ]
      ]

    --generatedFunD <- generatedFunDQ
    --runIO $ putStrLn $ pprint generatedFunD

  fmap pure generatedFunDQ
--      additionalArgs :: CodeGen
--      additionalArgs = "map (\\n -> \" a\" ++ show n) [1.." <> varCode "additionalArgs" <> staticCode "]"
--        go res 0 = res
--        go res n = go (staticCode (" a" ++ show n) : res) (n - 1)

maybeVarNameFromType :: Type -> Maybe Name
maybeVarNameFromType (VarT name) = Just name
maybeVarNameFromType (ConT (name @ (Name (OccName nameStr) _)))
  | S.member nameStr trivialTypes = Nothing
  | otherwise = Just name
maybeVarNameFromType (AppT f x) = maybeVarNameFromType f <|> maybeVarNameFromType x
maybeVarNameFromType _ = Nothing

varNameFromType :: Type -> Name
varNameFromType (ConT name) = name
varNameFromType (VarT name) = name
varNameFromType (all @ (AppT f x)) = case maybeVarNameFromType all of
  Just o -> o
  Nothing -> varNameFromType x
varNameFromType others = error $ "varNameFromType " ++ show others ++ " not implemented"

varNamesForNormalSlots :: [StrictType] -> [String]
varNamesForNormalSlots slots =
  let
    dupNames :: S.Set String
    dupNames = go S.empty S.empty rawNames where
      go res seen (nameStr : others) =
        if S.member nameStr seen then
          go (S.insert nameStr res) seen others
        else
          go res (S.insert nameStr seen) others
      go res _ _ = res

    rawNames = map (\(_, ty) -> case varNameFromType ty of Name (OccName str) _ -> lowerHead str) slots

    finalNames = go M.empty rawNames where
      go nameCount (nameStr : others) =
        if | S.member nameStr dupNames ->
            let
              nameCount' = M.insertWith (+) nameStr 1 nameCount
              serial = nameCount' M.! nameStr
            in
              (nameStr ++ show serial) : go nameCount' others
           | S.member nameStr reservedNames ->
            (nameStr ++ "0") : go nameCount others
           | otherwise ->
            nameStr : go nameCount others
      go _ _ = []
  in
    finalNames

transExprFromType :: Type -> CodeGen
transExprFromType = genExpr where
  genExpr :: Type -> CodeGen
  genExpr = \case
    VarT _ -> "id"
    ConT (Name (OccName name) _)
      | S.member name trivialTypes -> "id"
      | otherwise -> varCode "funPrefix" <> staticCode name <> varCode "additionalArgsExp"
    AppT ListT x -> "fmap (" <> genExpr x <> ")"
    AppT (ConT (Name (OccName "Maybe") _)) x -> "fmap (" <> genExpr x <> ")"
    AppT (AppT (TupleT 2) a) b -> "((" <> genExpr a <> ") *** (" <> genExpr b <> "))"
    AppT f (VarT _) -> genExpr f
    others -> error $ "exprFromType " ++ show others ++ " not implemented"

exprFromType :: String -> Type -> CodeGen
exprFromType name ty = "(" <> transExprFromType ty <> " " <> staticCode name <> ")"

lowerHead :: String -> String
lowerHead (c:cs) = toLower c : cs
lowerHead _ = []

collectAllNonTrivialComponent :: Name -> Q (S.Set Name)
collectAllNonTrivialComponent root = go S.empty (S.singleton root) where
  go res pending =
    case S.minView pending of
      Nothing ->
        return res
      Just (name, others)
        | S.member name res ->
          go res others
        | otherwise -> do
          info <- reify name
          go (S.insert name res) (nonTrivialComponentInInfo info `S.union` others)

nonTrivialComponentInType :: Type -> S.Set Name
nonTrivialComponentInType = \case
  ConT (name @ (Name (OccName nameStr) _))
    | S.member nameStr trivialTypes -> S.empty
    | isLower (head nameStr) -> S.empty
    | otherwise -> S.singleton name
  AppT f x -> nonTrivialComponentInType f `S.union` nonTrivialComponentInType x
  ListT -> S.empty
  TupleT _ -> S.empty
  VarT _ -> S.empty
  others -> error $ "nonTrivialComponentInType " ++ show others ++ " not implemented"

extractTyVarBndrNameStr :: [TyVarBndr] -> [String]
extractTyVarBndrNameStr (PlainTV (Name (OccName nameStr) _) : others) = nameStr : extractTyVarBndrNameStr others
extractTyVarBndrNameStr (KindedTV (Name (OccName nameStr) _) _ : others) = nameStr : extractTyVarBndrNameStr others
extractTyVarBndrNameStr _ = []

nonTrivialComponentInInfo :: Info -> S.Set Name
nonTrivialComponentInInfo = \case
  TyConI (DataD [] _ bndrs cons _) -> mconcat $ map nonTrivialComponentInCon cons
  TyConI (TySynD _ bndrs ty) -> nonTrivialComponentInType ty
  TyConI (NewtypeD [] _ bndrs con _) -> nonTrivialComponentInCon con
  others -> error $ "nonTrivialComponentInInfo " ++ show others ++ " not implemented"

nonTrivialComponentInCon :: Con -> S.Set Name
nonTrivialComponentInCon = \case
  NormalC _ slots -> mconcat (map (nonTrivialComponentInType . snd) slots)
  RecC _ slots -> mconcat (map (\(_, _, ty) -> nonTrivialComponentInType ty) slots)
  others -> error $ "nonTrivialComponentInCon " ++ show others ++ " not implemented"

genDataTransformer :: Info -> CodeGen
genDataTransformer =
  let
    conToDef tyNameStr (NormalC (Name (OccName conNameStr) _) slots) =
      let
        varNames = varNamesForNormalSlots slots
      in
        varCode "funPrefix" <> staticCode tyNameStr <> varCode "additionalArgsExp" <>
          " (" <> staticCode (intercalate " " (conNameStr : varNames)) <> ") = " <>
          intercalateCode " " (staticCode conNameStr : zipWith (\varNameStr (_, ty) -> exprFromType varNameStr ty) varNames slots) <>
          "\n"
    conToDef tyNameStr (RecC (Name (OccName conNameStr) _) slots) =
      let
        varNames = map (\(Name (OccName nameStr) _, _, _) -> nameStr) slots
      in
        varCode "funPrefix" <> staticCode tyNameStr <> varCode "additionalArgsExp" <>
          " (" <> staticCode (intercalate " " (conNameStr : varNames)) <> ") = " <>
          intercalateCode " " (staticCode conNameStr : zipWith (\varNameStr (_, _, ty) -> exprFromType varNameStr ty) varNames slots) <>
          "\n"
    conToDef tyNameStr others = error $ "genCon " ++ show others ++ " not implemented"
  in
    \case
      TyConI (DataD [] (Name (OccName tyNameStr) _) bndrs cons _) ->
        let
          typeSig = varCode "funPrefix" <> staticCode tyNameStr <> " :: " <> varCode "additionalArgsType" <> tyNameBndrStrCode <> " -> " <> tyNameBndrStrCode <> "\n"
          tyNameBndrStrCode = intercalateCode " " (map staticCode (tyNameStr : (extractTyVarBndrNameStr bndrs)))
        in
          mconcat $ typeSig : map (conToDef tyNameStr) cons
      TyConI (TySynD (Name (OccName tyNameStr) _) bndrs ty) ->
        let
          typeSig = varCode "funPrefix" <> staticCode tyNameStr <> " :: " <> varCode "additionalArgsType" <> tyNameBndrStrCode <> " -> " <> tyNameBndrStrCode <> "\n"
          tyNameBndrStrCode = intercalateCode " " (map staticCode (tyNameStr : (extractTyVarBndrNameStr bndrs)))
          def = varCode "funPrefix" <> staticCode tyNameStr <> varCode "additionalArgsExp" <> " a = " <> exprFromType "a" ty <> "\n"
        in
          typeSig <> def
      TyConI (NewtypeD [] (Name (OccName tyNameStr) _) bndrs con _) ->
        let
          typeSig = varCode "funPrefix" <> staticCode tyNameStr <> " :: " <> varCode "additionalArgsType" <> tyNameBndrStrCode <> " -> " <> tyNameBndrStrCode <> "\n" 
          tyNameBndrStrCode = intercalateCode " " (map staticCode (tyNameStr : (extractTyVarBndrNameStr bndrs)))
          def = conToDef tyNameStr con
        in
          typeSig <> def
      others -> error $ "genDataTransformer " ++ show others ++ " not implemented"
