import Control.Monad
import Control.Applicative
import Control.Arrow
import Data.Functor
import Data.List
import Data.Ord
import qualified Data.Map.Strict as M

--sortOn lens = sortBy (comparing lens)

oneTask = do
  [n, k] <- map read <$> (words <$> getLine) :: IO [Int]
  as <- map read <$> (words <$> getLine) :: IO [Int]

  let
    analyzed = foldl' nextStep M.empty (zip as [1..]) where
      nextStep acc (a, i) =
        M.insertWith (const (second (+ 1))) a (i, 1) acc

    valid = filter (\(_, (_, k')) -> k' >= k)
    order = sortOn (\(_, (i, _)) -> i)
    format ls =
      if null ls then
        [-1]
      else
        map fst ls

  putStrLn $ unwords . map show . format . order . valid . M.toList $ analyzed

main = do
  t <- read <$> getLine
  replicateM t $ oneTask
