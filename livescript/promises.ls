#!/usr/bin/env lsc
require! {
  rsvp: { Promise }
}

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

