require! request

count = 0
done = false

f = !->
  count := count + 1
  setImmediate f if not done

request 'http://caasigd.org/' !->
  console.log count, \done
  done := true

f!
