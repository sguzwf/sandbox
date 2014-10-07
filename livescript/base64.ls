uint6FromBase64 = ->
  if not it.charCodeAt then throw new Error 'should be a string'
  it = it.charCodeAt 0
  switch
  | 65 <= it < 91  => it - 65
  | 97 <= it < 123 => it - 97 + 26
  | 48 <= it < 64  => it - 48 + 52
  | it is 43       => 62
  | it is 47       => 63
  | otherwise      => throw new Error 'out of range'

base64FromUint6 = ->
  | 0  <= it < 26 => String.fromCharCode it + 65
  | 26 <= it < 52 => String.fromCharCode it + 97 - 26
  | 52 <= it < 62 => String.fromCharCode it + 48 - 52
  | it is 62      => \+
  | it is 63      => \/
  | otherwise     => throw new Error 'out of range'

arrayFromBase64 = ->
  it = Array::slice.call it
  result = []
  while it.length
    padding = 0
    c = it.shift!
    v = uint6FromBase64(c) .<<. 18
    c = it.shift!
    v .|.= uint6FromBase64(c) .<<. 12
    c = it.shift!
    if c isnt \= and c isnt undefined
      then v .|.= uint6FromBase64(c) .<<. 6
      else ++padding
    c = it.shift!
    if c isnt \= and c isnt undefined
      then v .|.= uint6FromBase64(c)
      else ++padding
    result
      ..push (v .&. 0xFF0000) .>>. 16
      ..push (v .&. 0x00FF00) .>>. 8  if padding < 2
      ..push (v .&. 0x0000FF)         if padding < 1
  result

base64FromArray = ->
  result = []
  while it.length
    padding = 0
    c = it.shift!
    v = c .<<. 16
    if (c = it.shift!) isnt undefined
      then v .|.= c .<<. 8
      else ++padding
    if (c = it.shift!) isnt undefined
      then v .|.= c
      else ++padding
    result
      ..push base64FromUint6 (v .&. 0xFC0000) .>>. 18
      ..push base64FromUint6 (v .&. 0x03F000) .>>. 12
      ..push if padding < 2
        then base64FromUint6 (v .&. 0x000FC0) .>>. 6
        else '='
      ..push if padding < 1
        then base64FromUint6 (v .&. 0x00003F)
        else '='
  result.join ''

module.exports =
  { arrayFromBase64, base64FromArray }
