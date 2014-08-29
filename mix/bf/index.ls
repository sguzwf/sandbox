$ = require 'jquery'
Brainfuck = require './bf'

data <- $.get './hello.bf'
(bf = Brainfuck!)
  ..output = -> document.write it
  ..exec data
