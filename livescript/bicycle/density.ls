#!/usr/bin/env lsc
global <<< require 'prelude-ls'
global <<< require './$'

density = request.get 'https://sheethub.com/data.gov.tw/%E5%90%84%E9%84%89%E9%8E%AE%E5%B8%82%E5%8D%80%E4%BA%BA%E5%8F%A3%E5%AF%86%E5%BA%A6?format=json' .then (.body)

columns = density.then (.sheet.columns) .then map (.name)
data    = density.then (.data)

zipped = do
  ks <- columns.then
  es <- data.then
  e  <- es.map
  lists-to-obj ks, e

show zipped
