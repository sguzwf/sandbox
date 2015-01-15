#!/usr/bin/env lsc
require! {
  rsvp: { Promise, all }:RSVP
  'prelude-ls': { apply }
}

RSVP.on \error -> console.log ...

wrap    = -> if Array.isArray it then all it else Promise.resolve it
p       = -> Promise.resolve it
promisy = (f) -> (...args) -> wrap args .then (args) -> wrap apply f, args
log     = promisy console.log
add     = promisy (+)

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
  (@_name, @_friend) ~>
  name: ->
    that = this
    new Promise (resolve, reject) ->
      setTimeout (-> resolve that._name), 300
  friend: ->
    that = this
    new Promise (resolve, reject) ->
      setTimeout (-> resolve that._friend), 300
var opal
ruby = People \ruby
opal = People \opal, ruby
ruby._friend = opal

start-time = Date.now!
ps =
  * Promise.resolve ruby
      .then (.friend!)
      .then (.friend!)
      .then (.name!)
  * ruby.name!
apply log, ps
all ps .then -> console.log Date.now! - start-time
