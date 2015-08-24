import System.IO

readTree :: IO [String]
readTree = do
  eof <- isEOF
  if eof then return []
         else do
           s <- getLine
           ss <- readTree
           return $ ss ++ [s]

writeTree :: [String] -> IO ()
writeTree [] = do
  return ()
writeTree (s:ss) = do
  putStrLn s
  writeTree ss

invertLine :: String -> String
invertLine [] = []
invertLine (c:cs)
  | c == '\\' = '/' : invertLine cs
  | c == '/'  = '\\' : invertLine cs
  | otherwise = c : invertLine cs

main = do
  ss <- readTree
  writeTree $ fmap invertLine ss

