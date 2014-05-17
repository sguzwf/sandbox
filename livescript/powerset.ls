powerset = ([x, ...xs]) ->
  | not x     => [[]]
  | otherwise => let ys = powerset xs => ys ++ [[x] ++ .. for ys]

console.log powerset []
console.log powerset [1 2 3]

# this is not the filterM
wat = (f, [x, ...xs]) -->
  | not x     => [[]]
  | otherwise =>
    (for flg in f x => for wat f, xs => if flg then [x] ++ .. else ..)
      .reduce (p, c) -> p ++ c

powerset$ = wat -> [true false]

console.log powerset$ []
console.log powerset$ [1 2 3]
