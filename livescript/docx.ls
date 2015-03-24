#!/usr/bin/env lsc
require! {
  'mammoth'
}

log = -> it.then -> console.log it.value
log mammoth.convertToMarkdown path: './wool.docx'

/*
# output

```markdown
## <a id="865996809909120-sigil_toc_id_6"></a>1

  __*霍斯頓一步步爬上樓梯走向死亡，而孩子們正在上面玩。他聽到震耳欲聾肆無忌憚的笑鬧聲。只有無憂無慮的孩子才有辦法笑得這麼開心。霍斯頓步履沈重，繞著螺旋梯，一圈又一圈，一步步往上爬，老舊的鞋子重重踩在鐵梯板上，腳步聲在樓梯井嗡嗡迴盪。*__

```
*/
