{ apply } = require 'prelude-ls'

# Awesome!
# https://github.com/gkz/LiveScript/issues/426#issuecomment-29270436
P = do ->
  unit = (a) -> Promise.resolve a
  bind = (p, f) -> p.then -> f it
  lift = (f) -> (...args) -> Promise.all args .then apply f
  { unit, bind, lift }

