{English, Chinese, Japanese} = require './lorem'

console
  # LoremHelpers
  ..log English.lorem-words 2
  ..log English.lorem-sentences 2
  ..log English.lorem-paragraphs 2
  ..log English.lorem-name!
  ..log English.lorem-email!
  ..log English.lorem-image '350x150'
  ..log English.lorem-image '350x150' random-color: true
  ..log English.lorem-image '350x150' background-color: '#16161D'
  ..log English.lorem-image '350x150' color: '#F90'
  ..log English.lorem-image '350x150' text: '<not-a-tag/>'
  ..log English.lorem-date?!
  # ZhLoremHelpers
  ..log Chinese.zh-lorem-name!
  ..log Chinese.zh-lorem-name-pinyin!
  ..log Chinese.zh-lorem-email!
  ..log Chinese.zh-lorem-words 20
