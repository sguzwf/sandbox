require! {
  fs
  request
}

request do
  method: \GET
  url: 'http://localhost:8081/books/two-tigers/audio.mp3'
  encoding: \binary
  (e, r, body) ->
    remote = new Buffer(body, \binary)
    local = fs.readFileSync './audio.mp3'
    console
      ..log remote
      ..log local
