#!/usr/bin/env lsc

require! {
  path
  canvas: Canvas
  # PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/opt/X11/lib/pkgconfig npm install canvas
  'opentype.js': opentype
}

/*
# 字型對了，你的設計才能做對？

講者： justfont 創辦人 葉俊麟

下面一樣是失真的筆記：

  * 「一個國家的內文字型與國民素質息息相關」 - 鳥海 修
  * 用手描字來學習字型設計
  * 識字只是第一塊，再來才是今天提到的這些進階議題
  * 對中英字認識多了，才能談中英搭配
  * 然後就要提排版跟造字
  * [字取其辱](https://www.facebook.com/groups/annoyfonts/)
  * [更多？](https://www.facebook.com/evenwu/posts/10152438505035718)
  * 主動光源會讓橫劃顯細

*/

font-path = path.resolve process.env.HOME, 'Library/Fonts/NotoSansCJKtc-Regular.otf'

/*
## 框線

  * 字面框
  * 1% 對閱讀經驗的影響
  * 東國酬愛鬱靈鷹袋，各有各的特點
  * 小塚明體之所以是 94% ，可能是因為在日文中配上假名不會那麼擁擠
  * 中文沒有這個詞，姑且用襯線來稱呼
  * 小塚黑體是個有襯線的黑體，沒有喇叭口
  * 蒙納宋，框不是正方的
  * 橫排讀的時候字會跳動？豎排卻非常 OK
  * 中文字其實豎排非常安定（以一為例）

*/

err, font <- opentype.load font-path

/*
## 骨架

  * 空間配置，中宮
  * 標題中宮緊縮，內文中宮放鬆，到什麼程度呢？
  * 文鼎黑體的特色：有圓體的弧線
  * 蘭亭黑，本來設計來用在報紙印刷上，把中宮放鬆到極限，求小字也清楚
  * 但是很不好讀 XD
  * 蒙納黑，字型楷化

*/

canvas = new Canvas 100 100
ctx    = canvas.getContext \2d
font.draw ctx, '東'

/*
## 筆畫

  * glyph 的細節
  * 蒙納宋粗體的沾粘
  * 文鼎細明的結尾
  * [Hiragino 明朝](http://zh.wikipedia.org/wiki/Hiragino)
  * 游明朝，圓潤

*/

image = ctx.getImageData 0 0 100 100
console.log image

/*
## 繼續介紹字型

  * 華康儷宋，經典
  * 為什麼 90% ？
  * 明體和黑體的骨架要分別設計嗎？
  * 成熟的信黑體

*/
