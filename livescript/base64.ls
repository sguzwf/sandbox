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
  | it is 62      => '+'
  | it is 63      => '/'
  | otherwise     => throw new Error 'out of range'

arrayFromBase64 = ->
  result = []
  end = 0
  v = 0
  s = []
  for i from 0 til it.length
    c = it[i]
    if c is '=' then ++end
    offset = (3 - i % 4) * 6
    v .|.= uint6FromBase64(c) .<<. offset if not end
    if offset is 0
      s.push (v .&. 0xFF)
      v .>>.= 8
      s.push (v .&. 0xFF)
      v .>>.= 8
      s.push v
      while (v = s.pop!) isnt undefined
        result.push v
      v = 0
  while end--
    result.pop!
  result

module.exports = {uint6FromBase64, base64FromUint6, arrayFromBase64}
