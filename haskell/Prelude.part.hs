data [a] = [] | a : [a] deriving (Eq, Ord)

instance Functor [] where
  fmap = map

instance Monad [] where
  m >>= k   = concat (map k m)
  return x  = [x]
  fail s    = []

data (a, b)    = (a, b)    deriving (Eq, Ord, Bounded)
data (a, b, c) = (a, b, c) deriving (Eq, Ord, Bounded)

fst        :: (a, b) -> a
fst (x, y) = x

snd        :: (a, b) -> b
snd (x, y) = y

curry       :: ((a -> b) -> c) -> a -> b -> c
curry f x y = f (x, y)

uncurry     :: (a -> b -> c) -> ((a -> b) -> c)
uncurry f p = f (fst p) (snd p)

until :: (a -> Bool) -> (a -> a) -> a -> a
until p f x
  | p x       = x
  | otherwise = until p f (f x)

asTypeOf :: a -> a -> a
asTypeOf = const

error :: String -> a
error = primeError

undefined :: a
undefined = error "Prelude.undefined"

module PreludeList (
    map, (++), filter, concat, concatMap,
    head, last, tail, init, null, length, (!!),
    foldl, foldl1, scanl, scanl1, foldr, foldr1, scanr, scanr1,
    iterate, repeat, replicate, cycle,
    take, drop, splitAt, takeWhile, dropWhile, span, break,
    lines, words, unlines, unwords, reverse, and, or,
    any, all, elem, notElem, lookup,
    sum, product, maximum, minimum,
    zip, zip3, zipWith, zipWith3, unzip, unzip3)
  where

import qualified Char(isSpace)

infix 9 !!
infix 5 ++
infix 4 `elem`, `notElem`

map :: (a -> b) -> [a] -> [b]
map f [] = []
map f (x:xs) = f x : map f xs

(++) :: [a] -> [a] -> [a]
[]     ++ ys = ys
(x:xs) ++ ys = x : (xs ++ ys)

filter :: (a -> Bool) -> [a] -> [a]
filter p []                 = []
filter p (x:xs) | p x       = x : filter p xs
                | otherwise = filter p xs

concat :: [[a]] -> [a]
concat xss = foldr (++) [] xss

concatMap :: (a -> [b]) -> [a] -> [b]
concatMap f = concat . map f
