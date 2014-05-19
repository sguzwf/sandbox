function A() {
  this.foo = "bar";
}

var a0 = new A, a1 = new A;

a0.foo = "buz";

console.log(a0.foo, a1.foo, A.prototype.foo);

function B() {}
B.prototype.foo = "bar";

var b0 = new B, b1 = new B;

b0.foo = "buz";

console.log(b0.foo, b1.foo, B.prototype.foo);
