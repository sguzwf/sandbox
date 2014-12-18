require! request

count = 0
done = false

f = !->
  count := count + 1
  console.log count
  setImmediate f if not done # blocked

request 'http://caasigd.org/' !->
  console.log count, \done
  done := true

f!
