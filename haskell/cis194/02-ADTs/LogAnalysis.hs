{-# OPTIONS_GHC -Wall #-}
-- module LogAnalysis where

import Control.Monad
import Log

parseSplit :: [String] -> LogMessage
parseSplit ("I":time:msg) = LogMessage Info t (unwords msg) where
  t = read time :: TimeStamp
parseSplit ("W":time:msg) = LogMessage Warning t (unwords msg) where
  t = read time :: TimeStamp
parseSplit ("E":level:time:msg) = LogMessage (Error l) t (unwords msg) where
  l = read level :: Int
  t = read time :: TimeStamp
parseSplit msg = Unknown $ unwords msg

parseMessage :: String -> LogMessage
parseMessage s = parseSplit $ words s

parse :: String -> [LogMessage]
parse s = fmap parseMessage $ lines s

testPrint :: [String] -> IO ()
testPrint = foldM (\_ s -> putStrLn s) ()

insert :: LogMessage -> MessageTree -> MessageTree
insert (Unknown _) tree = tree
insert log Leaf = Node Leaf log Leaf
insert log@(LogMessage _ t _) (Node leftTree log'@(LogMessage _ t' _) rightTree)
  | t < t' = Node (insert log leftTree) log' rightTree
  | t > t' = Node leftTree log' (insert log rightTree)
  | t == t' = Node leftTree log rightTree -- bye, old log

build :: [LogMessage] -> MessageTree
build logs = foldl (\tree log -> insert log tree) Leaf logs

inOrder :: MessageTree -> [LogMessage]
inOrder Leaf = []
inOrder (Node left log right) = (inOrder left) ++ [log] ++ (inOrder right)

whatWentWrong :: [LogMessage] -> [String]
whatWentWrong [] = []
whatWentWrong ((LogMessage log _ msg):ls) = case log of
  (Error level) -> if level > 50 then msg : rest else rest
  _ -> rest
  where rest = whatWentWrong ls

main :: IO ()
main = do
  logs <- testParse parse 5523 "./error.log"
  --testPrint $ fmap show $ (inOrder . build) logs
  testPrint $ (whatWentWrong . inOrder . build) logs

