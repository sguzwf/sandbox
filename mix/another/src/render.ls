#!/usr/bin/env lsc
require! {
  'react': React
  './index'
}

Index = React.createFactory index

[,, ...args] = process.argv

if not args.0
  console.log "usage"

comp = try require args.0

if not comp
  console.log "#{args.0}: component not found"
else
  Comp = React.createFactory comp
  #html = React.renderToString Comp!
  html = React.renderToStaticMarkup Comp!
  console.log "<!DOCTYPE html>#{html}"

