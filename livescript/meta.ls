MetaBug = (kind) ->
  (name) ->
    @kind = kind
    @name = name

IrregularBug = new MetaBug 'irregular'
RegularBug = new MetaBug 'regular'

console.log JSON.stringify new IrregularBug 'foo'
console.log JSON.stringify new RegularBug 'bar'
