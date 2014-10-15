#!/usr/bin/env lsc
require! request

request do
  method: 'POST'
  uri: 'https://www.ethercalc.org/_/ckiarss5uv'
  body: 'foo, bar, foobar, boo'
  (err, res, body) -> console.log body
.setHeader 'content-type': 'text/csv'
