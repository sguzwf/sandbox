#!/usr/bin/env lsc
require! {
  request
  rsvp: { Promise: P, all, hash }:RSVP
  'prelude-ls': { is-type, apply }
}

RSVP.on \error console.log

###
# Utils
is-promise = -> it?then and it?catch

Promise = ->
  switch it
  | is-type 'Array'  it => all it
  | is-type 'Object' it => hash it
  | is-promise it       => it
  | otherwise           => P.resolve it

# not exactly a Functor
# fmap :: Functor Promise  => (a -> b) -> (Promise a -> Promise b)
fmap = (f) -> (...args) -> all args .then (args) -> Promise f `apply` args

###
# Functions
delay = fmap (v) -> new P (resolve, reject) ->
  (-> resolve v) `setTimeout` 500

ask-moedict = fmap (c) -> new P (resolve, reject) ->
  err, res, body <- request "https://www.moedict.tw/~#{ encodeURIComponent c }.json"
  switch
  | err                     => reject err
  | res.statusCode isnt 200 => reject res.statusCode
  | otherwise               => resolve JSON.parse body
for-pinyin  = fmap (.heteronyms.0.pinyin - /<br>.*/)

log = fmap console.log
now = fmap (time = 0) -> Date.now! - time

###
# Main
log 'sequential', now delay delay now!
log delay('para'), delay('llel')

chars = <[遙 望 暖 毛 毛]>
log `apply` chars
log `apply` (for chars => .. |> ask-moedict |> for-pinyin)
