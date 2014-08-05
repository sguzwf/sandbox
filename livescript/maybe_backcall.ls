
# Maybe monad implementation:

m = (value) -> (f) ->
    | f         => f value # as bind
    | otherwise => value   # as unwrap

Nothing = -> Nothing
Just    = m

# For convenience
unit    = Just
nothing = Nothing
just    = Just



# Demonstration on how to use Maybe monad:
test =
  * do
      x <- (just 5)
      x <- (unit x + 1)
      unit 1 - x
  * do
      x <- nothing
      x <- (unit x + 1)
      unit 1 - x

console.log (for m in test => do m)

# inspired by https://www.facebook.com/groups/javascript.tw/permalink/513042925463717/
test =
  * just brother: just skills: just name: just \hello
    just brother: nothing

f = ->
  {brother} <- it
  {skills } <- brother
  {name   } <- skills
  name

console.log (for m in test => do f m)
