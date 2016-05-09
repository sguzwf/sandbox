module Main where

import Data.Functor
import Control.Monad

main = do
  count <- read <$> getLine :: IO Int
  let
    step acc@(x:_) 0 = return acc
    step acc n = do
      [a, b] <- map read <$> (words <$> getLine) :: IO [Double]
      step ((a, b):acc) (n-1)
  pts@(p:ps) <- step [] count
  let
    pairs = zip pts (ps ++ [p])
    distance ((x0, y0), (x1, y1)) = sqrt $ (x0 - x1) ** 2 + (y0 - y1) ** 2
  putStrLn $ show $ sum $ map distance pairs
