var uint6FromBase64, base64FromUint6, arrayFromBase64, base64FromArray;
uint6FromBase64 = function(it){
  if (!it.charCodeAt) {
    throw new Error('should be a string');
  }
  it = it.charCodeAt(0);
  switch (false) {
  case !(65 <= it && it < 91):
    return it - 65;
  case !(97 <= it && it < 123):
    return it - 97 + 26;
  case !(48 <= it && it < 64):
    return it - 48 + 52;
  case it !== 43:
    return 62;
  case it !== 47:
    return 63;
  default:
    throw new Error('out of range');
  }
};
base64FromUint6 = function(it){
  switch (false) {
  case !(0 <= it && it < 26):
    return String.fromCharCode(it + 65);
  case !(26 <= it && it < 52):
    return String.fromCharCode(it + 97 - 26);
  case !(52 <= it && it < 62):
    return String.fromCharCode(it + 48 - 52);
  case it !== 62:
    return '+';
  case it !== 63:
    return '/';
  default:
    throw new Error('out of range');
  }
};
arrayFromBase64 = function(it){
  var result, padding, c, v, x$;
  it = Array.prototype.slice.call(it);
  result = [];
  while (it.length) {
    padding = 0;
    c = it.shift();
    v = uint6FromBase64(c) << 18;
    c = it.shift();
    v |= uint6FromBase64(c) << 12;
    c = it.shift();
    if (c !== '=' && c !== undefined) {
      v |= uint6FromBase64(c) << 6;
    } else {
      ++padding;
    }
    c = it.shift();
    if (c !== '=' && c !== undefined) {
      v |= uint6FromBase64(c);
    } else {
      ++padding;
    }
    x$ = result;
    x$.push((v & 0xFF0000) >> 16);
    if (padding < 2) {
      x$.push((v & 0x00FF00) >> 8);
    }
    if (padding < 1) {
      x$.push(v & 0x0000FF);
    }
  }
  return result;
};
base64FromArray = function(it){
  var result, padding, c, v, x$;
  result = [];
  while (it.length) {
    padding = 0;
    c = it.shift();
    v = c << 16;
    if ((c = it.shift()) !== undefined) {
      v |= c << 8;
    } else {
      ++padding;
    }
    if ((c = it.shift()) !== undefined) {
      v |= c;
    } else {
      ++padding;
    }
    x$ = result;
    x$.push(base64FromUint6((v & 0xFC0000) >> 18));
    x$.push(base64FromUint6((v & 0x03F000) >> 12));
    x$.push(padding < 2 ? base64FromUint6((v & 0x000FC0) >> 6) : '=');
    x$.push(padding < 1 ? base64FromUint6(v & 0x00003F) : '=');
  }
  return result.join('');
};
module.exports = {
  arrayFromBase64: arrayFromBase64,
  base64FromArray: base64FromArray
};
