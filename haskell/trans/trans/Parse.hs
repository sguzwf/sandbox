module Parse
  ( getAllModules
  , prettyPrintAllModules
  ) where

import Language.Haskell.Exts.Annotated
import Language.Haskell.Exts.Pretty
import qualified Data.Map.Strict as M
import System.IO
import System.FilePath
import Control.Exception

{-
# 2016-04-27

Workshop 要從 transpiler 重新開始，使用 [stack][stack] 管理開發套件，寫自己的
transpiler 。

stack 基本操作：

  ```
  stack new my-project
  cd my-project
  stack setup
  stack build
  stack exec my-project-exe
  ```

stack 生出來的 project 檔是 `stack.yaml` ，裡面指定了 GHC 的版本、套件、架構等。
我還不清楚那裡面指定的 `extra-deps` 與 cabel 檔中的有何不同？只記得用 cabel 時手
動裝本地套件很麻煩。

那個 `my-project-exe` 要回到 `.cabel` 中修改 `executable` 。

[stack]: http://docs.haskellstack.org/en/stable/README/

Cindy 建議先讀過的 lib 有：

  * [haskell-src-exts][src-exts]

    這個看過好幾次了，在做那個愚蠢的、不 pretty 的 print 時都看網頁查 type 。那
    時看的是 Language.Haskell.Exts.Syntax ，後來看的是 Language.Haskell.Exts.
    Annotated.Syntax 。要注意的是，後者的結構跟前者完全不同。

    不過才五個月啊。

    [src-exts]: https://hackage.haskell.org/package/haskell-src-exts

  * [Language.Haskell.Exts.Annotated.Syntax][annotated-syntax]

    看來 Language.Haskell.Exts.Syntax 是不用看了。

    ann 和 amap 是操作 annotations 的[工具][afuncs]。那天 Alex 有提過。前者把
    annotation 拔出來，後者只對 annotation 作用。

    [annotated-syntax]: https://hackage.haskell.org/package/haskell-src-exts-1.17.1/docs/Language-Haskell-Exts-Annotated-Syntax.html
    [afuncs]: https://github.com/haskell-suite/haskell-src-exts/blob/master/src/Language/Haskell/Exts/Annotated/Syntax.hs#L1052

  * [Language.Haskell.Exts.Annotated.Parser][annotated-parser]

    全部看嗎？還是只看一下 `parse` 就好？

    [annotated-parser]: https://hackage.haskell.org/package/haskell-src-exts-1.17.1/docs/Language-Haskell-Exts-Annotated-Parser.html

  * [Language.Haskell.Exts.Pretty][pretty]

    記得這鬼東西 pretty 完就變回 Haskell 了，跟有縮排的 AST 不同。
    但對我們來說，更需要後者。那時試著看 TH 的，發現 [Text.PrettyPrint][HPJ] ，
    但沒看懂。現在不知道看不看得懂 XDXD

    [pretty]: https://hackage.haskell.org/package/haskell-src-exts-1.17.1/docs/Language-Haskell-Exts-Pretty.html
    [HPJ]: https://hackage.haskell.org/package/pretty-1.1.3.3/docs/Text-PrettyPrint.html

  * [Haskell Standard Library][libraries]

    [libraries]: https://downloads.haskell.org/~ghc/latest/docs/html/libraries/

  * [Data.Map.Strict][data-map-strict]

    [data-map-strict]: https://downloads.haskell.org/~ghc/latest/docs/html/libraries/containers-0.5.6.2/Data-Map-Strict.html

  * [System.IO][system-io]

    [system-io]: https://downloads.haskell.org/~ghc/latest/docs/html/libraries/base-4.8.2.0/System-IO.html

  * [System.FilePath][system-filepath]

    搞半天，原來 Hackage 多用 [Haddock][Haddock] [註解][CodingStyle]。

    但是 Base 的 lhs 多用 \begin{code} 跟 \end{code} 這樣還有什麼意思呢？ github
    上只有到 2001 年的 commit ，不知道最早是不是就這樣？

    [system-filepath]: https://downloads.haskell.org/~ghc/latest/docs/html/libraries/filepath-1.4.0.0/System-FilePath-Posix.html
    [Haddock]: https://www.haskell.org/haddock/
    [CodingStyle]: https://ghc.haskell.org/trac/ghc/wiki/Commentary/CodingStyle

  * [Control.Exception][control-exception]

    作者是[嘴吐][cokmett] category theory 的 ekmett ！

    [control-exception]: https://downloads.haskell.org/~ghc/latest/docs/html/libraries/base-4.8.2.0/Control-Exception.html
    [cokmett]: https://www.reddit.com/r/haskell/comments/1ssa5g/edward_kmett_such_mathematical_wow_algebraic/

---

  探しものは何ですか？見つけにくいものですか？

-}

-- 從 Main.hs 來看，該從 getAllModules ，還有 prettyPrintAllModules 看起。
-- getAllModules 在做的是從給定的檔案內容中取得 Module 名稱與所 imports 的其他
-- Modules 名稱，再存到 Map 中。
--
-- 它們在 IO () 裡面的理由大概是...，可以在 main 的 do notation 下直接寫，不用
-- 再 pure 或 return 一下？如果只是 ParseResult (M.Map String (Module
-- SrcSpanInfo)) 的話， main 該怎麼改呢？
getAllModules :: String -> IO (ParseResult (M.Map String (Module SrcSpanInfo)))
getAllModules src =
  case parseModule src of
    ParseFailed loc msg -> return $ ParseFailed loc msg
    ParseOk mod -> do
      let
        modName = case mod of
          Module _ Nothing _ _ _ -> "Main"
          Module _ (Just (ModuleHead _ (ModuleName _ modName) _ _)) _ _ _ -> modName

        imports = moduleImports mod

      addMoreModules (M.singleton modName mod) imports

-- 存到 Map 中的工作，由 addMoreModules 完成。
-- 有趣的是，在 Haskell 中打兩次 M.Map String (Module SrcSpanInfo) 不是什麼問題
-- ，但 Java 中就會想用一個 <T> 解決就好。
addMoreModules :: M.Map String (Module SrcSpanInfo) -> [String] -> IO (ParseResult (M.Map String (Module SrcSpanInfo)))
addMoreModules = go where
  -- 我覺得常見的 `go acc []` 和 `go acc (m : ms)` 這種 local 遞迴用起來很像
  -- reduce/fold ，不知道作者是怎麼看的？
  go acc [] = return $ pure acc
  go acc (m : ms)
    | M.member m acc = go acc ms -- 已經 import  過了
    | m == "Prelude" = go acc ms -- 略過 Prelude
    | otherwise = do
      res <- getModule m
      case res of
        ParseFailed loc msg -> return (ParseFailed loc{srcFilename = m} msg)
        -- insert 後的 Map 變成下一次 go 的 acc 。 moduleImports 則從 mod 中取得
        -- 更多的 module names ，交給下次的 go 。
        ParseOk mod -> go (M.insert m mod acc) (moduleImports mod ++ ms)

moduleImports :: Module l -> [String]
-- Module 長這樣：
--   Module l (Maybe (ModuleHead l)) [ModulePragma l] [ImportDecl l] [Decl l]
-- 這裡只留下 [ImportDecl l]
moduleImports (Module _ _ _ imports _) = map takeOne imports where
  takeOne imp = case importModule imp of
    ModuleName _ modName -> modName

-- getModule 是包裝好的 parseModule
-- 原來 Control.Exception 用在這裡！
getModule :: String -> IO (ParseResult (Module SrcSpanInfo))
getModule modName = do
  let filename = modNameToPath modName
  catch
    ( do
      src <- readFile filename
      return (parseModule src)
    )
    (\e -> return $ ParseFailed (SrcLoc filename 0 0) (show (e :: SomeException)))

prettyPrintAllModules :: M.Map String (Module SrcSpanInfo) -> IO ()
prettyPrintAllModules = go . M.toAscList where
  go [] = return ()
  go ((modName, mod) : ms) = do
    putStrLn $ modName ++ ":"
    putStrLn $ prettyPrint mod
    putStrLn ""
    go ms

modNameToPath :: String -> FilePath
modNameToPath = go where
  go [] = extSeparator : "hs"
  go ('.' : ns) = pathSeparator : go ns
  go (n : ns) = n : go ns

