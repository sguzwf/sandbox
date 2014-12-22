#!/usr/bin/env lsc
require! {
  react: React
  htmltidy: { tidy }
}

{ div, span } = React.DOM

# Dont React?
Cue = React.createClass do
  displayName: 'Cue'
  componentDidMount: ->
    # * Can have post processing steps
    #   You can do what ever you want after the rendering
    #   by using componentDidMount() in the client,
    #   or renderToString() in the server.
  getDefaultProps: ->
    progress: 0
  notify: ->
    # * Can delay rendering after state/props change
    #   You can manage all your states outside the view.
    # * Don't have to reactively compose components
    #   You don't listen. You don't observe.
    owner = this
    while owner._owner => owner = owner._owner
    owner?props?onNotify ...
  render: ->
    div do
      className: 'cue'
      div do
        className: 'children'
        @props.children
        div do
          className: 'overlay'
          style:
            width: "#{@props.progress * 100}%"
          @props.children
Cue = React.createFactory Cue

App = React.createClass do
  displayName: 'App'
  render: ->
    Cue do
      progress: 0.01337
      span do
        className: 'foo'
        'Foo!'
      span do
        className: 'bar'
        'Bar!'
      span do
        className: 'quux'
        'Quux!'
App = React.createFactory App

tidy do
  React.renderToString App!
  { indent: on }
  (_, html) -> console.log html
