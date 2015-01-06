#!/usr/bin/env lsc

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
  * 兩邊的 object 也要一樣。

是指 props 嗎？）

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

/*
## LY

  * 寫 node 前是寫 PHP 的（笑）。
  * 兩個問題：
    * client side performance
    * SEO
  * 比較好支援 IE8 。
  * 有個不會用 Photoshop 但是寫得一手好 Angular 的設計師。
  * Angular 竟然淪落到作 markup （眾笑）。

不要一直捅自己的市長給問啊啊啊啊啊。

  * 模仿一個 app 。
  * 跟 Inbox 致敬。
  * 做得很漂亮，表示抄得很像（眾笑）。
  * 用 express ，分兩部分， API 和 render 。
  * client first 變成 component first 。

不知道對解決 component reuse 問題，有什麼想法？
LY: 可能被迫還是要 page-based 。永久的 uri ...。加上還有 CSS 的問題。不過還是覺得要往 component-based 發展啦。

  * es5-shim for IE8

vminpoly 也能很方便的接上去。

  * Flux
  * react-router

也好想找機會寫寫看 Flux 。

  * superagent
  * Auth: getToken
    * express-session
    * passport-session

LY 你人太好了。（還在捅自己的市長給問）

  * Dockerfile
  * ES6

*/

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

/*
# TonyQ

slide: http://slides.com/tonyq/jsconfasia-intro#/

  * 那美克星要爆炸了，還有六集可以逃。
  * 主題還是會以 JSConf Asia 為主。
  * 要辦 JSConf 得 follow 一些 guideline ，所以台灣先辦自己的 JSDC 。
  * 控制人數，不會太多人。
  * SVG
  * CSSConf
    * Airbnb 重構整個品牌的故事。
      * 一鍵切換兩組 theme 。除了 dashboard 。
      * 三個月。
    * CSS3DRender
    * Flex 垂直置中。
      * 八九種不同 cases 。
    * Black Magic
  * JSConf 2014
    * Isomorphic
    * PixelArt
    * Bad Form
    * Sensor Game
      * 用的是 Firefox OS Phone 。
    * 很多題目都是 'Why not?'
    * [WebTorrent](https://github.com/feross/webtorrent)
    * [dat](https://github.com/maxogden/dat)
    * phaser.io
    * node school
      * 走出家裡，參加或發起 community 。

比較一下 dat 和 [CASC](https://gist.github.com/galedric/b34f14dd93381498a7a1) 。

  * 前端要玩的太多，那就玩命吧 XD

*/

tidy do
  React.renderToString App!
  { indent: on }
  console.log

/*
## Notes

  * Fullstack Rocks 的教育訓練， 280k ：
    http://www.fullstackrocks.com/course-react/

  * 另外記得私下問一下，能不能去上這個：
    https://plus.google.com/+TataChen/posts/427He2vXHQA

原來已經有十二個人，也就是大約二十分之一在寫 Isomorphic JavaScript 了。

*/
