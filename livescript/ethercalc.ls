#!/usr/bin/env lsc
require! request

id = 'ckiarss5uv'

dimension = (id, done) ->
  request do
    method: 'GET'
    uri: "https://www.ethercalc.org/_/#id"
    (err, , body) ->
      return done err if err
      # tvf means 'text value format'
      {1:col, 2:row, 3:tvf} = /sheet:c:(\d+):r:(\d+):tvf:(\d+)/g.exec body
      done null, +col, +row

append-once = (id, row, done) ->
  options =
    method: 'POST'
    uri: "https://www.ethercalc.org/_/#id"
    body: row
  req = request options, (err, , body) -> done err, (body unless err)
  req =>..setHeader 'content-type': 'text/csv'

append = (id, row, done) ->
  limit = 3
  interval = 1000
  retry = limit
  :foobar let
    err,, before <- dimension id
    err,  command <- append-once id, row
    err,, after <- dimension id
    if retry--
      if before is after
        then setTimeout foobar, interval
        else done null, command
    else
      done new Error "Fail to append after #limit attempts."

err, command <- append id, 'fuzz,buzz'
throw err if err
console.log command
