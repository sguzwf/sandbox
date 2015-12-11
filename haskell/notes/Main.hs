module Main where
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

main = putStrLn $ show allColors
