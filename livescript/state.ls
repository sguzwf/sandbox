state = (o = {}) ->
  ((s) -> state {} <<< o <<< s)
    ..do = -> it o

foo = state name: \foo =>.. STR: 8 =>.. DEX: 9 =>.. CON: 8
  ..do console.log

bar = foo name: \bar =>.. INT: 10
  ..do console.log

bar = bar STR: 18
  ..do console.log
