#!/usr/bin/env lsc
DataURI = require 'datauri'
Base64  = require 'base64-js'
{arrayFromBase64, base64FromArray} = require './base64'
require! atob
require! fs

data = new DataURI './assets/ai.mp3'
console.log data.base64.length / 4 * 3

r = new Buffer atob data.base64
console.log "atob: #{r.length}"
fs.writeFile './assets/atob.mp3', r

r = new Buffer Base64.toByteArray data.base64
console.log "base64-js: #{r.length}"
fs.writeFile './assets/beatgammit.mp3', r

r = new Buffer arrayFromBase64 data.base64
console.log "homebrew: #{r.length}"
console.log data.base64.substring 0, 10
console.log base64FromArray(arrayFromBase64(data.base64))substring 0, 10
fs.writeFile './assets/homebrew.mp3', r
