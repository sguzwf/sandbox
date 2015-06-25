class Foo
  @hooks: []
  constructor: ->
    this.name = 'foo'
    hook this for hook in Foo.hooks
  register: (hook) -> Foo.hooks.push hook

foo = new Foo
foo.register (obj) -> obj.name += 'foobar'
bar = new Foo
bar.register (obj) -> obj.name += 'barfoo'
quux = new Foo

console.log foo.name, bar.name, quux.name
