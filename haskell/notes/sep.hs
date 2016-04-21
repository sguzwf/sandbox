module Main where

sepSeries :: [Double]
sepSeries = 0 : inner where
  inner = 0.5 : mix halfs (map (+ 0.5) halfs)
  halfs = map (/ 2) inner
  mix (a:as) (b:bs) = a : b : mix as bs

main :: IO ()
main = do
  putStrLn $ show $ take 16 sepSeries
