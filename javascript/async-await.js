#!/usr/bin/env 6to5-node
import request from 'superagent';

function log(p) {
  p.then((v) => console.log(v));
}

function pinyin(c) {
  return new Promise((resolve, reject) => {
    request
      .get(`https://moedict.tw/${c}.json`)
      .end((err, res) => {
        if (err) return reject(err);
        resolve(res.body.heteronyms[0].pinyin);
      });
  });
}

// reference: https://github.com/lukehoban/ecmascript-asyncawait
function spawn(genF) {
  return new Promise((resolve, reject) => {
    var gen = genF();
    function step(nextF) {
      var next;
      try {
        next = nextF();
      } catch (e) {
        reject(e);
        return;
      }
      if (next.done) {
        resolve(next.value);
        return;
      }
      Promise.resolve(next.value).then((v) => {
        step(() => gen.next(v) );
      }, (e) => {
        step(() => gen.throw(e) );
      });
    }
    step(() => gen.next(undefined) );
  });
}

function test() {
  return spawn(function *() {
    var a = yield pinyin('故'),
        b = yield pinyin('態'),
        c = yield pinyin('復'),
        d = yield pinyin('萌');
    return `${a} ${b} ${c} ${d}`;
  });
}

log(test());
