#!/usr/bin/env lsc
require! {
  'prelude-ls': { flip, concatMap }
}

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

# well, it works and looks like a filterM
cmap    = flip concatMap
cst     = (fst, snd) --> fst
filterM = (p, [x, ...xs]) -->
  | not x => [[]]
  | _
    flg <- cmap (p(x))
    ys  <- cmap filterM(p, xs)
    if flg then [[x] ++ ys] else [ys]
powerset$$ = filterM (cst([true, false]))

console.log powerset$$ []
console.log powerset$$ [1, 2, 3]
