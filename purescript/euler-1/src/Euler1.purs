module Euler1 where

import Data.Array
import qualified Data.Foldable as F

ns = range 0 999

multiples = filter (\n -> n % 3 == 0 || n % 5 == 0) ns

answer = F.sum multiples

