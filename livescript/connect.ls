require! connect
require! http

app = connect!
  #.use connect.cookieParser!
  .use (req, res) ->
    console.log req
    res.end!

http.createServer app .listen 8080
