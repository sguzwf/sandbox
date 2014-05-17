
# Maybe monad implementation:

m = (value) ->
  (f) ->
    | f         => f value # as bind
    | otherwise => value # as unwrap

Nothing = -> Nothing
Just = m

# For convenience
unit    = Just
nothing = Nothing
just    = Just



# Demonstration on how to use Maybe monad:
test = []

test.push(
  do do
    x <- (just 5)
    x <- (unit x + 1)
    unit 1 - x
)
test.push(
  do do
    x <- nothing
    x <- (unit x + 1)
    unit 1 - x
)

console.log(test)
