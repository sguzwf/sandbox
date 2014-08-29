{en, zh, jp} = require './lorem'

console
  # LoremHelpers
  ..log en.lorem-words 2
  ..log en.lorem-sentences 2
  ..log en.lorem-paragraphs 2
  ..log en.lorem-name!
  ..log en.lorem-email!
  ..log en.lorem-image '350x150'
  ..log en.lorem-image '350x150' random-color: true
  ..log en.lorem-image '350x150' background-color: '#16161D'
  ..log en.lorem-image '350x150' color: '#F90'
  ..log en.lorem-image '350x150' text: '<not-a-tag/>'
  ..log en.lorem-date?!
  # ZhLoremHelpers
  ..log zh.lorem-name!
  ..log zh.lorem-name-pinyin!
  ..log zh.lorem-email!
  ..log zh.lorem-words 20
  ..log zh.lorem-sentence!
  ..log zh.lorem-sentences 2
  ..log zh.lorem-paragraphs 2
  # JpLoremHelpers
  ..log jp.lorem-name!
