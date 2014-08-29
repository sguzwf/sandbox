class Brainfuck
  (@size = 3000) ~>
    # context
    @stack = []
    @pc = 0
    @memory = []
    @pointer = 0
  input:  -> ' '
  output: !-> # into the void
  exec:   !(program) ->
    program = Array::filter.call program, (in '><+-,.[]')
    # init
    @pc = 0
    @pointer = 0
    for i from 0 til @size => @memory[i] = 0
    # run
    while @pc < program.length
      switch program[@pc]
      | '>' => ++@pointer
      | '<' => --@pointer
      | '+' => ++@memory[@pointer]
      | '-' => --@memory[@pointer]
      | ',' => @memory[@pointer] = @input!charCodeAt.0 % 256
      | '.' => @output String.fromCharCode @memory[@pointer]
      | '[' => @stack.push @pc
      | ']' => (if @memory[@pointer] then @pc = @stack[*-1] else @stack.pop!)
      | _   => throw new Error 'unknown op'
      @pointer = (@pointer + @size) % @size
      ++@pc
module.exports = Brainfuck
