module Golf where

skip :: Int -> [a] -> [a]
skip len [] = []
skip len xs = case rest of
  [] -> []
  (y:ys) -> y : (skip len ys)
  where rest = drop len xs

skips :: [a] -> [[a]]
skips xs = map (flip skip xs) [0..len-1]
  where len = length xs

takeThree :: [Integer] -> [[Integer]]
takeThree list
  | length list < 3 = []
  | otherwise       = case list of
    (x:xs@(y:z:zs)) -> [(x:y:z:[])] ++ takeThree xs

isMaxima :: [Integer] -> Bool
isMaxima list
  | length list /= 3 = False
  | otherwise        = case list of
    (x:y:z:_) -> y > x && y > z

untakeThree :: [[Integer]] -> [Integer]
untakeThree [] = []
untakeThree (xs:xss)
  | length xs < 3 = untakeThree xss
  | otherwise = case xs of
    (x:y:z:[]) -> [y] ++ untakeThree xss

localMaxima :: [Integer] -> [Integer]
localMaxima = untakeThree . (filter isMaxima) . takeThree
