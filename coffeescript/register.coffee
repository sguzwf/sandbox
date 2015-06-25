class Foo
  @hooks: []
  @run: -> hook() for hook in Foo.hooks
  register: (hook) -> Foo.hooks.push hook

foo = new Foo
bar = new Foo

foo.register -> console.log 'foo'
bar.register -> console.log 'bar'

Foo.run()
