module Main where

import Data.List
import Data.Functor
import qualified Data.Map.Strict as M
import Control.Monad

main = do
  count <- read <$> getLine :: IO Int
  let
    step = do
      count <- read <$> getLine :: IO Int
      let
        getPair acc 0 = return acc
        getPair acc n = do
          [a, b] <- map read <$> (words <$> getLine) :: IO [Int]
          getPair ((a, b) : acc) (n - 1)
      pairs <- getPair [] count
      let
        pairs' = groupBy (\a b -> fst a == fst b)
               . sortBy (\a b -> fst a `compare` fst b)
               $ pairs
      putStrLn $ case length pairs == length pairs' of
        True -> "YES"
        False -> "NO"
  replicateM_ count step
