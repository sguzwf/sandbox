module Main where

{-
  2015-12-15

  - 不懂 Applicative ，更別論 pure 了。

  - Extend? Comonad?

  - Raja rajasharan@gmail.com 提到：

    `(>>=) :: m a -> (a -> m b) -> m b`

    換成：

    `(a -> m b) -> m a -> m b` ，也就是 `(a -> m b) -> (m a -> m b)`

    不是更好理解嗎？

    讓我想起，自己的 Monad 入門是從幫 JS Promise/A+ 做 lift ：

    `liftPromise :: (a -> b) -> p a -> p b`

    開始的。

    Joel Williamson joel.s.williamson@gmail.com 提到 Raja 講的就是：

    `(=<<) :: (a -> m b) -> m a -> m b`

    也可以靠 `flip` 實現： `flip (>>=)` 。
-}

{-
  2015-12-13

  - 原來是 `transExprFromType :: Type -> CodeGen` 的
    `AppT (AppT (TupleT 2) a) b -> "((" <> genExpr a <> ") *** (" <> genExpr b <> "))"`
    寫錯了。寫成：
    `AppT (AppT (TupleT 2) a) b -> "(" <> genExpr a <> ") *** (" <> genExpr b <> ")"`
    結果是少剝一層 XD

  - not a panacea
-}

{-
  2015-12-12

  - 看到 zoomcraft XD 記得查查 memcache 在哪個 repo ？

  - `genExpr :: Type -> CodeGen`
    原來 where 下面的 function 也可以寫 type 啊。

  - 終於會動了，抄都會抄錯。

  - 不知道 build 很慢是不是因為 type 很複雜害的？

  - runIO?

  - 18f2247 其實只快一點點？還是 Air 太慢？

    real    1m5.769s
    user    1m21.585s
    sys     0m41.418s

  - 原來「可以看到所有 Module 」指的是像 lookupTypeName 這類 function 。
    然後把結果分成 trivial 和 non-trivial 。

  - 原來也有 Kata 。像是 Introductory Haskell: Solving the Sorting-It-Out Kata 。

  - 只有 `deIfExp (If exp1 exp2 exp3)` 要自己寫。

  - 蟲：
    - `ConDecl (RecDecl name1 name2)` 最內層的 fmap 多包一層 `()` 。
    - `deIfDecl (DeprPragmaDecl srcLoc name)` 和
      `deIfDecl (WarnPragmaDecl srcLoc name)` 也一樣。
    - `deIfDeriving a = (((deIfQName) *** (fmap (deIfType))) a)` 也一樣。
    - `deIfExp (GenPragma string int1 int2 exp)`
    - `deIfGadtDecl (GadtDecl srcLoc name1 name2 type0)`
    - `deIfImportDecl (ImportDecl importLoc importModule importQualified importSrc importSafe importPkg importAs importSpecs)`
-}

{-
  2015-12-11

  - 不懂 TH 中的 |Lift| 是什麼？

  - `<>`?

  - 注意在 case 中， unionStatic as 的結果才是被拆成 StaticCode asStr : others 的。
    (desugar-template)
      unionStatic (a : as) =
        case (a, unionStatic as) of
          (StaticCode aStr, StaticCode asStr : others) -> StaticCode (aStr <> asStr) : others
          (_, as') -> a : as'
      unionStatic _ = []

  - `instance`? polymorphism? `pprint`?

  - GeneralizeNewtypeDeriving? MultiWayIf!
    下午 #haskell.tw 在討論 MultiWayIf 怎麼排版才好， cibs 大大建議用黏在一起的
    寫法： `if| ->` 好維持兩格空白縮排。 `if | ->` 前面五格，很難排，而換行才寫
    `|` 被評為：「就快要對齊了，又剛好歪掉」 XD
-}

{-
  2015-11-16

  Mark Carter alt.mcarter@gmail.com
    `\x -> (pred1 x) && (pred2 x)`?
  Benjamin Edwards edwards.benj@gmail.com
    `(&&) <$> pred1 <*> pred2`!
  Frerich Raabe raabe@froglogic.com
    `liftA2 (&&) pred1 pred2`!
  akash g akaberto@gmail.com
    `(pred1 &&& pred2) >>> uncurry (&&)` Arrow!
-}

{-
  2015-11-15

  amindfv@gmail.com
  one can use `:{` and `}:` to code in multiple lines in ghci

  :{
  let digs 0 =[0]
      digs x = (digs (x `div` 10)) ++ [(x `rem` 10)]
  :}
-}

{-
  2015-11-15

  amindfv@gmail.com
-}

data Color = RED | BLUE | YELLOW
  deriving (Show, Enum, Bounded)

allColors :: [Color]
allColors = [minBound..maxBound]

