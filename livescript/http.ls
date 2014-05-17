require! http

http.createServer (req, res) ->
  console.log req
  res.end!
.listen 8080
