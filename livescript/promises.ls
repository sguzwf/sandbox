#!/usr/bin/env lsc
require! {
  rsvp: { Promise, all }:RSVP
  'prelude-ls': { apply }
}

RSVP.on \error -> console.log ...

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

# a little implict
p       = -> Promise.resolve it
promisy = (f) -> (...args) -> all args .then (args) -> apply f, args
add     = promisy (+)
log     = promisy console.log

log add 41, p(43)