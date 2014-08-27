helpers = require './lorem'

console
  ..log helpers.lorem-words 2
  ..log helpers.lorem-sentences 2
  ..log helpers.lorem-paragraphs 2
  ..log helpers.lorem-name!
  ..log helpers.lorem-email!
  ..log helpers.lorem-image '350x150'
  ..log helpers.lorem-image '350x150' random-color: true
  ..log helpers.lorem-image '350x150' background-color: '#16161D'
  ..log helpers.lorem-image '350x150' color: '#F90'
  ..log helpers.lorem-image '350x150' text: '<not-a-tag/>'
  ..log helpers.lorem-date! if helpers.lorem-date
