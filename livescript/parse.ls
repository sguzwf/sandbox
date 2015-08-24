#!/usr/bin/env lsc
require! {
  'crypto'
  'bluebird': Promise
  'parse': { Parse }
}

Parse.initialize do
  \xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  \xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

save = ({ username, password }) ->
  user = new Parse.User
  hasher = crypto.createHash \md5
  hasher.update password
  password = hasher.digest \hex
  user.save { username, password }

load = ({ id }) ->
  query = new Parse.Query Parse.User
  query.get id

Promise.resolve { username: \nishio, password: \foobar }
  .then save
  .then load
  .then -> console.log it
  .catch -> console.log it
