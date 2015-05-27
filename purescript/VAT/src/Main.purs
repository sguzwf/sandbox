module Main where

import Math
import Data.Char
import Data.String (toCharArray)
import Data.Array
import Data.Foldable
import Debug.Trace

toDigit :: Char -> Number
toDigit c = toCharCode c - 48

shift :: Char -> Number -> Number
shift c 0 = 1 * toDigit c
shift c 1 = 2 * toDigit c
shift c 2 = 1 * toDigit c
shift c 3 = 2 * toDigit c
shift c 4 = 1 * toDigit c
shift c 5 = 2 * toDigit c
shift c 6 = 4 * toDigit c
shift c 7 = 1 * toDigit c

indexes :: [Char] -> [Number]
indexes cs = range 0 ((length cs) - 1)

sumDigits :: Number -> Number
sumDigits n = floor(n % 10) + floor(n / 10)

sumAll :: [Char] -> Number
sumAll cs = sum $ map sumDigits $ zipWith shift cs $ indexes cs

branches :: [Char] -> Boolean
branches cs@(_:_:_:_:_:_:c:_)
  | toDigit c == 7 = (sumAll cs) % 10 == 0 || (sumAll cs + 1) % 10 == 0
  | otherwise      = (sumAll cs) % 10 == 0

isVAT :: String -> Boolean
isVAT s = branches $ toCharArray s

main = do
  trace $ show $ map isVAT ["01515147", "01515189", "01515195", "01515224",
                            "01515239", "01515250", "01515293", "02076770",
                            "01989377", "01517314", "01681671", "01989279"]
