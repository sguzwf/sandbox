var A = function () {
  this.name = "a";
};

var B = function () {
  this.name = "b"
  return new A;
};

var o = new B;
console.log(o);

var o = Object.create(B);
o = B.call(o);
console.log(o);
