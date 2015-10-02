#!/usr/bin/env lsc
# ./search-bonus.ls | tee /dev/tty | pbcopy
request = require 'superagent-bluebird-promise'

global <<< require 'prelude-ls'
{ stdin } = process

search = ->
  p = request
    .get 'https://saleorderadmin.yfycpg.com/TVBuy_WService.asmx/GetFMWProducts?CategoryNo=&ActivityNo=&Points='
    .query Keyword: it
  Promise.all [it, p]

# main
lines = ''
stdin
  .resume!
  .on \data ->
    lines += it
  .on \end  ->
    lines := lines |> split /[\r\n]/ |> filter id
    ps = lines |> map search
    ps |> fold1 (acc, p) ->
      acc.then ([name, res]) ->
        console.log "'#{res.body?0?ProductNo or ''}', // #name"
        p
