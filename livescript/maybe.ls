
# Maybe monad implementation:
check-nothing = (f) ->
  (x) ->
    | x is Nothing  => Nothing
    | otherwise     => f x

bind = (f) -> (check-nothing f) do this

Nothing = -> Nothing
Nothing.bind = bind

Just = (x) ->
  ret = -> x
  ret.bind = bind
  ret

# For convenience
unit    = Just
nothing = Nothing
just    = Just



# Demonstration on how to use Maybe monad:

some-computation = (x) -> unit(x + 1).
              bind (x) -> unit(1 - x)

test = []

test.push (just 1).bind(some-computation)() # just -1
test.push (just 5).bind(some-computation)() # just -5
test.push  nothing.bind(some-computation)() # nothing

console.log(test)
