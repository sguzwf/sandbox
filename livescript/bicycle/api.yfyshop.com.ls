#!/usr/bin/env lsc
global <<< require 'prelude-ls'
global <<< require './$'

host = 'http://api.yfyshop.com:8080/Service'
site = 'GroupSale'

headersAndBody = ({ headers, body }) -> { headers, body }
onError = ({ message, status, body }) -> console.log { message, status, body }

fUser = request
  .post "#host/#site/user/login"
  .query do
    account:  'caasi.huang@yfyshop.com'
    password: 'asuka1'
  .then headersAndBody
  .then peek
  .catch onError
  .then inject -> console.log 'fUser'

fNothing = request
  .post "#host/#site/user/login"
  .then headersAndBody
  .then peek
  .catch onError
  .then inject -> console.log 'fNothing'

fWrongPassword = request
  .post "#host/#site/user/login"
  .query do
    account:  'caasi.huang@yfyshop.com'
    password: 'aaaaa'
  .then headersAndBody
  .then peek
  .catch onError
  .then inject -> console.log 'fWrongPassword'

fNoPassword = request
  .post "#host/#site/user/login"
  .query do
    account:  'caasi.huang@yfyshop.com'
  .then headersAndBody
  .then peek
  .catch onError
  .then inject -> console.log 'fNoPassword'

fEmptyPassword = request
  .post "#host/#site/user/login"
  .query do
    account:  'caasi.huang@yfyshop.com'
    password: ''
  .then headersAndBody
  .then peek
  .catch onError
  .then inject -> console.log 'fEmptyPassword'

