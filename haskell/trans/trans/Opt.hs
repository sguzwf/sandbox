module Opt
  ( Options(..) -- * 這個 `(..)` 是？
  , getOpts
  ) where

import System.Environment
import System.Console.GetOpt
import Data.Default

data Options = Options
  { optDesugar :: !Bool
  }
instance Default Options where
  def = Options
    { optDesugar = False
    }

-- * OptDescr 是？
options :: [OptDescr (Options -> Options)]
options =
  [ Option ['d'] ["desugar"]
    (NoArg (\opts -> opts { optDesugar = True }))
    "show the desugarred basic haskell source"
  ]

getOpts :: IO Options
getOpts = do
  argv <- getArgs
  -- * Permute 和順序有關嗎？
  case getOpt Permute options argv of
    (o, n, []) -> return (foldl (flip id) def o)
    (_, _, errs) -> ioError (userError (concat errs ++ usageInfo header options))
      where
        header = "Usage: trans [OPTIONS...] < source"
