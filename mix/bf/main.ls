require! fs
Brainfuck = require './bf'

err, data <- fs.readFile './hello.bf'
throw err if err
(bf = Brainfuck!)
  ..output = -> process.stdout.write it
  ..exec data.toString!
