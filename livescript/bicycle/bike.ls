require! {
  # language
  'bluebird': Promise
  'liftp'
  # file-system
  'fs'
  'path'
  # string
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

module.exports = {
  Promise, lift,
  fs, path,
  entities, punycode, unorm,
  request, xml2js, html2jade, soap
}
