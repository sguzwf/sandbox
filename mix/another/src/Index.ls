require! {
  'react': { Component, { html, head, title, body, div }:DOM }:React
}

class Index extends Component
  (@props) ->
  render: ~>
    html do
      null
      head do
        null
        title null, 'the index'
      body do
        null
        div do
          className: 'app'
          'a strange way to use React'

module.exports = Index

