import Golf

main = do
  putStrLn $ show $ skips "ABCD"
  putStrLn $ show $ skips "hello!"
  putStrLn $ show $ skips [1]
  putStrLn $ show $ skips [True, False]
  putStrLn $ show $ skips ([] :: String)
  putStrLn $ show $ localMaxima [2, 9, 5, 6, 1]
  putStrLn $ show $ localMaxima [2, 3, 4, 1, 5]
  putStrLn $ show $ localMaxima [1, 2, 3, 4, 5]

