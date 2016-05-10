module Main where

import System.IO
import Data.List

getDigits :: String -> String
getDigits ([]) = ""
getDigits (_:[]) = ""
getDigits (_:_:str) = go str where
  go [] = ""
  go (' ':cs) = ""
  go (c:cs) = case any ((==) c) "+-0123456789" of
    False -> go cs
    True -> c : go cs

isTitle :: String -> Bool
isTitle = any ((==) '：')

getTitle :: String -> String
getTitle = filter ((/=) '：')

main = do
  let
    putResult title sum = putStrLn $ title ++ "：$" ++ show sum
    process [] _ = do
      eof <- isEOF
      if eof
        then return ()
        else do
          line <- getLine
          case isTitle line of
            False -> process [] 0
            True -> process (getTitle line) 0
    process title sum = do
      eof <- isEOF
      if eof
        then do
          putResult title sum
          return ()
        else do
          line <- getLine
          case isTitle line of
            True -> do
              putResult title sum
              process (getTitle line) 0
            False -> do
              --putStrLn $ getDigits line
              let
                entry = case length line of
                  0 -> 0
                  _ -> read $ getDigits line :: Int
              process title (sum + entry)
  process [] 0
