#!/usr/bin/env lsc
require! {
  fs
  'form-data': FormData
}

path = '../../ChineseCUBES/cnl/test/sample.odp'

odp = fs.readFileSync path
stream = fs.createReadStream path

form0 = new FormData
form0.append \file odp

form1 = new FormData
form1.append \file stream

console
  ..log form0
  ..log form1
