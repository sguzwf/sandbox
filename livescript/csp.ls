#!/usr/bin/env lsc

# This is inspired by O3, but I dont understand CSP yet.
# https://blog.othree.net/log/2015/02/14/csp/

class Chan
  (@buffer = [], @consumers = []) ~>
  put: (v) ->
    @buffer.push v
    @run!
  take: (cb) ->
    @consumers.push cb
    @run!
  run: ~>
    if @buffer.length and @consumers.length
      @consumers.shift! @buffer.shift!
    this
  lift: (f) ~> (...args) ~>
    # Things in args are all channels, so we take one value from each channel
    # and apply f to them, then put the return value back to this channel.
    # I am not sure if I can call this method `lift` here, but the idea is
    # coming from the concept of lifting.
    # reductRight is a good tool to compose a callback chain.
    run = args.reduceRight do
      # We have to pass an array to the callback(cb), so we take one value from
      # the current channel, and call the callback with a new array.
      # What we have to return will be the next callback, so it will pass the
      # previous array(xs) to us.
      (cb, channel) ->
        (xs) -> channel.take -> cb xs.concat [it]
      # At the end of the callback chain, we have to put the result of
      # calculation to this channel.
      (xs) ~> @put f.apply this, xs
    # Extend run() to operate this channel automatically.
    old-run = @run
    @run = ~>
      old-run!
      run []
    this



chan0 = Chan!
chan1 = Chan!
chan2 = Chan!
out0  = Chan!
out1  = Chan!

add3 = out0.lift (a, b, c) -> a + b + c
add3 chan0, chan1, chan2
mul3 = out1.lift (a, b, c) -> a * b * c
mul3 chan0, chan1, chan2

out0.take console.log
out1.take console.log
out0.take console.log
out0.take console.log
chan0
  .put 1
  .put 2
  .put 1
  .put 5
chan1
  .put 1
  .put 2
  .put 2
  .put 10
chan2
  .put 1
  .put 2
  .put 3
  .put 15

