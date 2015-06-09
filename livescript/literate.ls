#!/usr/bin/env lsc
require! {
  'fs'
  'markdown-to-ast'
  'prelude-ls': { concat-map, filter, id, join }
  'livescript': LiveScript
}

[,, ...files] = process.argv

should-run = [];
const extract = ({ type, children = [], value = '' }) ->
  result = children |> concat-map extract |> filter id |> join "\n"
  switch
  | type is 'CodeBlock' => value + result
  | otherwise           => result

for filepath in files
  err, data <- fs.readFile filepath, encoding: \utf-8
  LiveScript.run extract markdown-to-ast.parse data

