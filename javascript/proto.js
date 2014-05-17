var A, B, C;

A = function() {};
A.prototype.foo = "bar";
A.prototype.getFoo = function() {
  return this.foo;
};

B = new A();
B.foo = "ping";

C = new A();

console.log(B.getFoo());
console.log(C.getFoo());
