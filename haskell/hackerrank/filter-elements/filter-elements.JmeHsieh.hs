module hackerrank where

import Data.List

orderedElem :: [Int] -> [Int]
orderedElem = foldl (\r x -> if x `elem` r then r else r++[x]) []

unorderedGrouping :: [Int] -> [[Int]]
unorderedGrouping = group . sort

orderedGrouping :: [Int] -> [[Int]]
orderedGrouping = (\(es, gs) -> (es >>= (\e -> filter (\(x:_) -> x == e) gs))) . apply2
  where apply2 = (,) <$> orderedElem <*> unorderedGrouping

result :: [Int] -> Int -> [Int]
result a k = check $ filter ((>= k) . length) $ orderedGrouping a
  where check n     | n == [] = [-1]
                    | otherwise = map head n
