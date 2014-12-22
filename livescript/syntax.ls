#!/usr/bin/env lsc

segment = (str, parts = []) ->
  re = new RegExp parts.join('|'), \g
  parts = []
  lastIndex = 0
  while r = re.exec str
    in-between = str.substring lastIndex, r.index
    if in-between.length
      parts.push do
        text: str.substring lastIndex, r.index
        actived: false
    parts.push do
      text: r.0
      actived: true
    lastIndex = r.index + r.0.length
  if lastIndex isnt str.length
    parts.push do
      text: str.substring lastIndex
      actived: false
  parts

console.log segment '我想擁抱憤怒的猴子，吃點果子。' <[擁抱 憤怒 猴子]>
