import Control.Monad
import qualified Data.HashMap as Map
import qualified Data.List as List

readInt :: String -> Int
readInt = read

getNums :: IO [Int]
getNums = getLine >>= return . words >>= return . (map readInt)

getCountMapAndRevUniqList :: [Int] -> (Map.Map Int Int, [Int])
getCountMapAndRevUniqList = foldl f (Map.empty, [])
  where
    f (m, l) n = (rm, rl)
      where
        count = case Map.lookup n m of
          Just c -> c
          Nothing -> 0
        rm = Map.insert n (count + 1) m
        rl = if count == 0 then n:l else l

appearAtLeast k countMap n = (Map.findWithDefault 0 n countMap) >= k

solve = do
  [_, k] <- getNums
  arr <- getNums
  let (countMap, revUniqArr) = getCountMapAndRevUniqList arr
  let appearAtLeastK = appearAtLeast k countMap
  let ans = filter appearAtLeastK $ reverse revUniqArr
  putStrLn $ if List.null ans
    then "-1"
    else unwords $ map show ans

main = do
  t <- getNums >>= return . head
  forM [1..t] $ \x -> solve
