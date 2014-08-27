helpers = require './lorem'

console
  ..log helpers.lorem-words 2
  ..log helpers.lorem-sentences 2
  ..log helpers.lorem-paragraphs 2
  ..log helpers.lorem-name!
  ..log helpers.lorem-email!
  ..log helpers.lorem-date! if helpers.lorem-date
