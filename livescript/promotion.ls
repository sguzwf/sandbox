#!/usr/bin/env lsc
require! {
  'superagent-bluebird-promise': request
  'moment'
}

get-promotions = ->
  request
    .get 'https://saleorderadmin.yfycpg.com/TVBuy_WService.asmx/GetFMWPromotionActivities'
    .then ->
      console.log moment!format!
      if not it.headers['access-control-allow-origin']
        console.log it.headers
        console.log it.body
    .catch -> console.error it
  setTimeout get-promotions, 10000
get-promotions!
