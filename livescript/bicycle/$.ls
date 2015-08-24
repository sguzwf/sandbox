require! {
  # language
  'bluebird': Promise
  'liftp'
  # file-system
  'fs'
  'path'
  # string
  'json-stable-stringify': stringify
  'punycode'
  'entities'
  'unorm'
  # API
  'superagent-bluebird-promise': request
  'xml2js'
  'html2jade'
  'soap'
}

lift = liftp Promise.all
show = lift console.log
stringify = lift stringify

inject = (f) -> (a) -> f a; a
peek = inject console.log.bind console

module.exports = {
  Promise, lift, inject, show, peek
  fs, path,
  stringify, entities, punycode, unorm,
  request, xml2js, html2jade, soap
}
