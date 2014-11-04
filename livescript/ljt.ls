#!/usr/bin/env lsc
require! {
  'prelude-ls': { concat-map, is-type }
}

log = console.log

##
# building blocks
empty   = (.length is 0)
is-a    = (p, a)    --> if p a then [a] else []
infix   = (f, g, j) --> concat-map g, f j
sum     = (f, g, j) --> (f j) ++ (g j)
or-else = (f, g, j) --> if empty (resl = f j) then g j else resl
guards  = (g, f, j) --> if empty g j then [] else f j
when$   = (f, g, j) --> if empty g j then [j] else f j

values = ->
  | is-type \String it => []
  | otherwise          => for key, val of it => val
keys = ->
  | is-type \String it => []
  | otherwise          => for key, val of it => key

deep  = (f, j) --> j |> f `or-else` (values `infix` deep f)
multi = (f, j) --> j |> f `sum` (values `infix` multi f)

##
# playground
foo = ->
  | is-type \String it => /foo/exec it
  | otherwise          => false
bar = ->
  | is-type \String it => /bar/exec it
  | otherwise          => false
is-foo = is-a foo
is-bar = is-a bar
has-foo-and-bar = values `infix` (is-foo `infix` is-bar)
has-foo-or-bar  = values `infix` (is-foo `sum` is-bar)
first-foo = deep is-foo
#every-foo = multi is-foo

grand-values = values `infix` values
sq-values = values `sum` values

obj =
  a: \foo
  b: \bar
  c:
    d: \foobar
    e: \buz
    f:
      g: \foo

obj |> values          |> log
obj |> grand-values    |> log
obj |> sq-values       |> log
obj |> has-foo-and-bar |> log
obj |> has-foo-or-bar  |> log
#obj |> deep is-foo     |> log # FIXME: why?
obj |> multi is-foo    |> log
