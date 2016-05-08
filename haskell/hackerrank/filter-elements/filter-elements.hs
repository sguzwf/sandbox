module Main where

import Data.List
import qualified Data.Map.Strict as M

main = do
  line <- getLine
  let
    setCount = read line :: Int
    processSet 0 = return ()
    processSet n = do
      let readList = (map read) . words :: String -> [Int]
      line <- getLine
      let _ : k : [] = readList line
      line <- getLine
      let
        xs = zip (readList line) [0..]
        go acc (x, i) = case M.member x acc of
          True -> M.adjust (\(i, count) -> (i, count + 1)) x acc
          False -> M.insert x (i, 1) acc
        rs = map (\(x, (i, count)) -> show x)
           . sortBy (\(x, (i, _)) (y, (j, _)) -> compare i j)
           . filter (\(x, (i, count)) -> count >= k)
           . M.toList
           $ foldl go M.empty xs
      putStrLn $ case length rs of
        0 -> "-1"
        _ -> unwords $ rs
      processSet (n - 1)
  processSet setCount
