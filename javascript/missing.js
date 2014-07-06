slice = Array.prototype.slice;

Object.prototype.method_missing = function (name, args) {
  console.log(name, args);
}

Object.prototype.invoke = function () {
  var args = slice.call(arguments, 0);
  var name = args.shift();

  if (this[name] !== undefined) {
    return this[name].apply(this, args);
  } else {
    this.method_missing(name, args);
    return null;
  }
};

o = {
  a: function () {
    console.log('a');
  }
};

o.invoke('a');
o.invoke('b');

