#!/usr/bin/env lsc
require! {
  rsvp: { Promise, all, hash }:RSVP
  'prelude-ls': { apply, is-type }
}

RSVP.on \error -> console.log ...

wrap = ->
  switch
  | it |> is-type 'Array'  => all it
  | it |> is-type 'Object' => hash it
  | otherwise              => Promise.resolve it
p       = -> Promise.resolve it
promisy = (f) -> (...args) -> all args .then (args) -> wrap f `apply` args
log     = promisy console.log
add     = promisy (+)

log p(41), 43
log add 41, p(43)

# begin
get = (p, cb) -> p.then cb

pa = new Promise (resolve, reject) ->
  setTimeout (-> resolve 'hello'), 1000

pb = new Promise (resolve, reject) ->
  setTimeout (-> resolve 'world'), 500

# print ASAP
pa.then console.log
pb.then console.log

# print in order #0
[pa, pb]reduce do
  (sofar, curr) ->
    sofar
      .then -> curr
      .then -> console.log ...
  Promise.resolve!

# print in order #1
do
  a <- get pa
  b <- get pb
  console.log "#a #b"

# more usages for you
class People
  (@name_, @friend_) ~>
  name:~
    -> new Promise (resolve, reject) ~>
      (~> resolve @name_) `setTimeout` 300
    (v) -> @name_ = v
  friend:~
    -> new Promise (resolve, reject) ~>
      (~> resolve @friend_) `setTimeout` 300
    (v) -> @friend_ = v
var opal
ruby = People \ruby
opal = People \opal, ruby
ruby.friend = opal

start-time = Date.now!
ps =
  * Promise.resolve ruby
      .then (.friend)
      .then (.friend)
      .then (.name)
  * ruby.name
apply log, ps
all ps .then -> console.log Date.now! - start-time
