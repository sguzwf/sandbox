#!/usr/bin/env lsc
require! {
  'prelude-ls': { flip, concat-map }
}

cmap = flip concat-map

do
  a <- cmap [2, 3,  5]
  b <- cmap [7, 9, 11]
  a * b
|> console.log
