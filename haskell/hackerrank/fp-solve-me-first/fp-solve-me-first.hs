module Main where

main = do
  let getInt = getLine >>= return . read
  a <- getInt
  b <- getInt
  putStrLn $ show $ a + b
