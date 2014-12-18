/*
# React 社群小聚 3 - Notes

以下紀錄不是逐字稿。肯定有誤差。

## 開場

  * SPA
    希望不是 RIA 還魂 XD
  * BaaS
  * Full Stack
    啊！溝通成本！我現在覺得卡卡的也是因為沒跨入這塊！
    但後端斷太久，不如砍掉重鍊。
    * Isomorphic
      下一步要了解 reuse bussiness logic 。
  * DevOP
    * docker
      雖然在用 dokku 但是其實不是很懂 docker 。
  * Full Stack DevOP
    獨角獸中的獨角獸，請用金條將他留下來。

*/

require! {
  react: React
  htmltidy: { tidy }
}

{ div, span } = React.DOM

/*
## Art Pai

  * 希望開跟不開 JavaScript 的結果是一樣的。（Isomorphic）
  * Progressive Enhancement!
  * 兩邊都要是 React render 出來的 HTML 才能成功 mount 喔！
  * 兩邊的 object 也要一樣。（是指 props 嗎？）
  * 整個 browsify ，沒有 minify 大概 1Mb ，然後整個站只要送 AJAX 就好。
  * 還在學 Flux 。
  * 希望可以跟 web component 看齊，這樣用什麼 framework 都能 reuse components 。

## LY 補充

  * 在 server-side 也有 localStorage 可以用。
  * 但這樣 client 和 server 兩邊的 localStorage 要同步。

*/

# rethink react-vtt
Cue = React.createClass do
  displayName: 'Cue'
  getDefaultProps: ->
    progress: 0
  render: ->
    div do
      className: 'cue'
      div do
        className: 'overlap'
        style:
          width: "#{@props.progress * 100}%"
        @props.children ######### 想起 Angular 的 transclude
      div do                  #
        className: 'children' #
        @props.children #######
Cue = React.createFactory Cue

App = React.createClass do
  displayName: 'App'
  render: ->
    Cue do
      className: 'my-cue'
      progress: 0.01337
      span do
        className: 'little-sister'
        '小紅帽'
      span {} '，'
      span do
        className: 'big-wolf'
        '大野狼'
App = React.createFactory App

tidy do
  React.renderToStaticMarkup App!
  { indent: on }
  console.log

###
# Notes
###
# Fullstack Rocks 的教育訓練， 280k ：
# http://www.fullstackrocks.com/course-react/
#
# 另外記得私下問一下，能不能去上這個：
# https://plus.google.com/+TataChen/posts/427He2vXHQA
#
# 原來已經有十二個人，也就是大約二十分之一在寫 Isomorphic JavaScript 了。
