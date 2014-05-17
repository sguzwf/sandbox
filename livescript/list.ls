
# List monad implementation:

check-empty = (f) ->
  (x) ->
    | x is Empty => Empty
    | otherwise => f.apply null, arguments

# hmmm..., not sure
concat = (xs, ys) ->
  | xs is Empty => ys
  | ys is Empty => xs
  | otherwise   =>
    Cons do xs, concat(xs.tail, ys)

map = (f, xs) ->
  | xs is Empty => Empty
  | otherwise   =>
    concat (check-empty f)(do xs), map(f, xs.tail)

toArray = (xs) ->
  | typeof xs isnt \function => [xs]
  | xs is Empty              => []
  | otherwise                =>
    toArray(do xs).concat toArray(xs.tail)

bind = (f) -> map f, this

Empty = -> Empty
Empty.tail = Empty
Empty.bind = bind

Cons = (head, tail = Empty) ->
  ret = -> head
  ret.tail = tail
  ret.bind = bind
  ret


# For convenience
unit  = Cons
empty = Empty
cons  = Cons



# Demonstration on how to use List monad:

some-computation = (x) -> unit(x + 1).
              bind (x) -> unit(1 - x)

test = []

test.push (unit 1).bind some-computation # [-1]
test.push (unit 5).bind some-computation # [-5]
test.push    empty.bind some-computation # empty



# Let's see list comprehension:

list = cons 0, cons 1, cons 2, cons 3, cons 4 # [0, 1, 2, 3, 4]



# [x*2 | x <- [0..5], x % 2 == 0]                         # [0, 4, 8]
test.push list.bind((x) -> if x % 2 == 0 then unit(x * 2) else empty)
# Also equivalent to this in Haskell:
# [0..5] >>= \x -> if mod x 2 == 0 then return (x * 2) else []
# or:
# do{ x <- [0..5]; if mod x 2 == 0 then return (x * 2) else [] }



# [x + y | x <- [0..1], y <- [1..2]]                      # [1, 2, 2, 3]
test.push(
  do
    x <- (cons 0, cons 1).bind
    y <- (cons 1, cons 2).bind
    unit x + y
)

# Also equivalent to this in Haskell:
# [0..1] >>= \x -> [1..2] >>= \y -> return (x + y)
# or:
# do{ x <- [0..1]; y <- [1..2]; return (x + y) }



# powerset :: [a] -> [[a]]
powerset = (xs) ->
  | xs is Empty => cons empty, empty
  | otherwise   =>
    take <- (cons true, cons false).bind
    ys <- powerset(xs.tail).bind
    if take then unit cons(do xs, ys)
            else unit ys
# Also equivalent to this in Haskell:
# powerset []     = [[]]
# powerset (x:xs) = [True, False] >>= \take -> powerset xs
#                                 >>= \ys   -> if take then return (x:ys)
#                                              else         return ys
# or:
# powerset []     = [[]]
# powerset (x:xs) = do
#   take <- [True, False]
#   ys   <- powerset xs
#   if take then return (x:ys)
#   else         return ys

# [[1,2,3],[1,2],[1,3],[1],[2,3],[2],[3],[]]
test.push powerset cons 1, cons 2, cons 3



#console.log(require('util').inspect(test, false, null))
console.log test.map (e) -> toArray e
