module RuntimeSource where

import Data.String

genInit :: IsString a => a
genInit = "//var util = require('./ULC-util.js');\n\
\//var pretty_closure = util.pretty_closure;\n\
\\n\
\//var fs = require('fs');\n\
\\n\
\function clone_env(env){\n\
\  var ctor = new Function;\n\
\  ctor.prototype = env;\n\
\  return new ctor;\n\
\}\n\
\\n\
\function clone_array(array){\n\
\  var out = new Array(array.length), i;\n\
\  for(i=0; i<array.length; ++i)\n\
\    out[i] = array[i];\n\
\  return out;\n\
\}\n\
\\n\
\function weak_normal_form(closure, cb){\n\
\  //console.log('weak_normal_form');\n\
\  //console.log(pretty_closure(closure, 1));\n\
\  var lam, env2, new_lam, new_closure, app_cont;\n\
\  switch(closure.expr[0]){\n\
\    case 'dat':\n\
\      return closure;\n\
\\n\
\    case 'var':\n\
\      if( closure.env[closure.expr[1]] ){\n\
\        new_closure = weak_normal_form(closure.env[closure.expr[1]], cb);\n\
\        if( !new_closure )\n\
\          return;\n\
\        closure.env = new_closure.env;\n\
\        closure.expr = new_closure.expr;\n\
\      }\n\
\      return closure;\n\
\\n\
\    case 'lam':\n\
\      return closure;\n\
\\n\
\    case 'app':\n\
\      app_cont = function(lam){\n\
\        if( lam.expr[0]==='int' ){\n\
\          new_lam = {\n\
\            expr: clone_array(lam.expr),\n\
\            env: lam.env\n\
\          };\n\
\          --new_lam.expr[2];\n\
\          new_lam.expr.push({expr: closure.expr[2], env: closure.env});\n\
\          new_closure = weak_normal_form(new_lam, cb);\n\
\          if( !new_closure )\n\
\            return;\n\
\        }\n\
\        else if( lam.expr[0]==='lam' ){\n\
\          env2 = clone_env(lam.env);\n\
\          env2[lam.expr[1]] = {expr: closure.expr[2], env: closure.env};\n\
\          new_closure = weak_normal_form({expr: lam.expr[2], env: env2}, cb);\n\
\          if( !new_closure )\n\
\            return;\n\
\        }\n\
\        else{\n\
\          throw 'non-appable app: ' + JSON.stringify(lam.expr);\n\
\        }\n\
\        closure.env = new_closure.env;\n\
\        closure.expr = new_closure.expr;\n\
\        return closure;\n\
\      };\n\
\\n\
\      lam = weak_normal_form({expr: closure.expr[1], env: closure.env}, function(lam){\n\
\        var res = app_cont(lam);\n\
\        if( res )\n\
\          cb(res);\n\
\      });\n\
\      if( lam )\n\
\        return app_cont(lam);\n\
\      else\n\
\        return;\n\
\\n\
\    case 'int':\n\
\      if( closure.expr[2]===0 ) {\n\
\        new_closure = closure.expr[3].apply(closure.env, closure.expr.slice(4).concat([cb]));\n\
\        if( !new_closure )\n\
\          return;\n\
\        closure.env = new_closure.env;\n\
\        closure.expr = new_closure.expr;\n\
\      }\n\
\      return closure;\n\
\  }\n\
\}\n\
\\n\
\var input_buffer = '';\n\
\var input_eof = false;\n\
\var input_wait = null;\n\
\\n\
\function run(expr, env, done){\n\
\  var i;\n\
\\n\
\  var cont = function(res){ // continuation?\n\
\    res = weak_normal_form(res, cont);\n\
\    if( res )\n\
\      done(res);\n\
\  };\n\
\  return weak_normal_form({expr: ['app', expr, null], env: env}, cont);\n\
\}\n\
\\n\
\var env = {};\n"

genPreludeLambda :: IsString a => a
genPreludeLambda = "env['True'] = {\n\
\  // so one can write false condition at the begining?\n\
\  expr: ['lam', 'is-false', ['lam', 'is-true', ['var', 'is-true']]],\n\
\  env: env\n\
\};\n\
\\n\
\env['False'] = {\n\
\  expr: ['lam', 'is-false', ['lam', 'is-true', ['var', 'is-false']]],\n\
\  env: env\n\
\};\n\
\\n\
\env['#I'] = {\n\
\  expr: ['lam', 'n', ['lam', 'f', ['app', ['var', 'f'], ['var', 'n']]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(:)'] = {\n\
\  // so one can write is-nil condition at the begining!\n\
\  expr: ['lam', 'a', ['lam', 'as', ['lam', 'is-nil', ['lam', 'is-cons', ['app', ['app', ['var', 'is-cons'], ['var', 'a']], ['var', 'as']]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['[]'] = {\n\
\  expr: ['lam', 'is-nil', ['lam', 'is-cons', ['var', 'is-nil']]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(+)'] = {\n\
\  expr: ['lam', 'a', ['lam', 'b', ['app', ['var', 'a'], ['lam', 'a#', ['app', ['var', 'b'], ['lam', 'b#', ['app', ['var', 'I#'], ['app', ['app', ['var', '(+#)'], ['var', 'a']], ['var', 'b']]]]]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(-)'] = {\n\
\  expr: ['lam', 'a', ['lam', 'b', ['app', ['var', 'a'], ['lam', 'a#', ['app', ['var', 'b'], ['lam', 'b#', ['app', ['var', 'I#'], ['app', ['app', ['var', '(-#)'], ['var', 'a']], ['var', 'b']]]]]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(*)'] = {\n\
\  expr: ['lam', 'a', ['lam', 'b', ['app', ['var', 'a'], ['lam', 'a#', ['app', ['var', 'b'], ['lam', 'b#', ['app', ['var', 'I#'], ['app', ['app', ['var', '(*#)'], ['var', 'a']], ['var', 'b']]]]]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['div'] = {\n\
\  expr: ['lam', 'a', ['lam', 'b', ['app', ['var', 'a'], ['lam', 'a#', ['app', ['var', 'b'], ['lam', 'b#', ['app', ['var', 'I#'], ['app', ['app', ['var', '(quotInt#)'], ['var', 'a']], ['var', 'b']]]]]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['mod'] = {\n\
\  expr: ['lam', 'a', ['lam', 'b', ['app', ['var', 'a'], ['lam', 'a#', ['app', ['var', 'b'], ['lam', 'b#'], ['app', ['var', 'I#'], ['app', ['app', ['var', '(remInt#)'], ['var', 'a']], ['var', 'b']]]]]]]],\n\
\  env: env\n\
\};\n"

genPreludeNative :: IsString a => a
genPreludeNative = "// lambda calculus char to js char\n\
\function lc_char_to_js_char(lc_char){\n\
\  if( lc_char.length==4 ){ // XXX: need an example\n\
\    switch(lc_char.charAt(2)){\n\
\      case 'n': return '\\n';\n\
\      case 's': return ' ';\n\
\      default: return lc_char.charAt(2);\n\
\    }\n\
\  }\n\
\  else\n\
\    return lc_char.charAt(1);\n\
\}\n\
\function js_str_to_lc_str(js_str){\n\
\  var gen = function(i){\n\
\    if( i<js_str.length )\n\
\      return {expr: ['lam', 'is-cons', ['lam', 'is-nil', ['app', ['app', ['var', 'is-cons'], ['var', \"'\"+js_str.charAt(i)+\"'\"]], ['int', 'js_str_to_lc_str', 0, gen, i+1]]]], env: {}};\n\
\    else\n\
\      return {expr: ['lam', 'is-cons', ['lam', 'is-nil', ['var', 'is-nil']]], env: {}};\n\
\  };\n\
\  return {expr: ['int', 'js_str_to_lc_str', ['lam', 'is-nil', ['var', 'is-nil']]], env: {}};\n\
\}\n\
\function lc_str_to_js_str(lc_str){\n\
\  var out = '';\n\
\  var take_cons = function(a, as){\n\
\    out += lc_char_to_js_char(weak_normal_form(a).expr[1]);\n\
\    weak_normal_form({\n\
\      expr: ['app', ['app', as.expr, ['int', 'lc_str_to_js_str-cons', 2, take_cons]], ['int', 'lc_str_to_js_str-nil', 0, take_nil]],\n\
\      env: as.env\n\
\    });\n\
\  };\n\
\  var take_nil = function(){};\n\
\  weak_normal_form({\n\
\    expr: ['app', ['app', lc_str.expr, ['int', 'lc_str_to_js_str-cons', 2, take_cons]], ['int', 'lc_str_to_js_str-nil', 0, take_nil]],\n\
\    env: lc_str.env\n\
\  });\n\
\  return out;\n\
\}\n\
\\n\
\env['Y#'] = {\n\
\  expr: ['lam', 'f', ['app', ['lam', 'x', ['app', ['var', 'f'], ['app', ['var', 'x'], ['var', 'x']]]], ['lam', 'x', ['app', ['var', 'f'], ['app', ['var', 'x'], ['var', 'x']]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['[]'] = {\n\
\  expr: ['lam', 'is-nil', ['lam', 'is-cons', ['var', 'is-nil']]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(:)'] = {\n\
\  expr: ['lam', 'a', ['lam', 'as', ['lam', 'is-nil', ['lam', 'is-cons', ['app', ['app', ['var', 'is-cons'], ['var', 'a']], ['var', 'as']]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['(+#)'] = {\n\
\  expr: ['int', '(+#)', 2, function(a, b){\n\
\    return {expr: ['dat', weak_normal_form(a).expr[1] + weak_normal_form(b).expr[1]], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['(-#)'] = {\n\
\  expr: ['int', '(-#)', 2, function(a, b){\n\
\    return {expr: ['dat', weak_normal_form(a).expr[1] - weak_normal_form(b).expr[1]], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['(*#)'] = {\n\
\  expr: ['int', '(*#)', 2, function(a, b){\n\
\    return {expr: ['dat', weak_normal_form(a).expr[1] * weak_normal_form(b).expr[1]], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['quotInt#'] = {\n\
\  expr: ['int', 'quotInt#', 2, function(a, b){\n\
\    return {expr: ['dat', (weak_normal_form(a).expr[1] / weak_normal_form(b).expr[1]) | 0], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['remInt#'] = {\n\
\  expr: ['int', 'remInt#', 2, function(a, b){\n\
\    return {expr: ['dat', weak_normal_form(a).expr[1] % weak_normal_form(b).expr[1]], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['(<=#)'] = {\n\
\  expr: ['int', '(<=#)', 2, function(a, b){\n\
\    return {expr: ['dat', (weak_normal_form(a).expr[1] <= weak_normal_form(b).expr[1]) | 0], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['(==#)'] = {\n\
\  expr: ['int', '(==#)', 2, function(a, b){\n\
\    return {expr: ['dat', (weak_normal_form(a).expr[1] == weak_normal_form(b).expr[1]) | 0], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['chr#'] = {\n\
\  expr: ['int', 'chr#', 1, function(n){\n\
\    return {expr: ['dat', String.fromCharCode(n.expr)], env: env};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['ord#'] = {\n\
\  expr: ['int', 'ord#', 1, function(ch){\n\
\    return {expr: ['dat', ch.expr.charCodeAt(0)], env: env}\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['show-int'] = {\n\
\  expr: ['int', 'show-int', 1, function(num){\n\
\    num = weak_normal_form(num);\n\
\    return weak_normal_form(js_str_to_lc_str(''+num.expr[1]));\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['read-int'] = {\n\
\  expr: ['int', 'read-int', 1, function(str){\n\
\    return {expr: ['var', lc_str_to_js_str(str) | 0], env: {}};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\var outBuffer = '';\n\
\\n\
\env['putChar#'] = {\n\
\  expr: ['int', 'putChar', 2, function(ch, s){\n\
\    ch = weak_normal_form(ch);\n\
\    if( ch.expr[1]=='\\n' ){\n\
\      console.log(outBuffer);\n\
\      outBuffer = '';\n\
\    }else{\n\
\      outBuffer += ch.expr[1];\n\
\    }\n\
\    return {expr: ['lam', 'p', ['app', ['app', ['var', 'p'], s], ['lam', 'a', ['var', 'a']]]], env: {}};\n\
\  }],\n\
\  env: env\n\
\};\n\
\\n\
\env['putChar'] = {\n\
\  expr: ['lam', 'ch', ['app', ['var', 'ch'], ['lam', 'ch#', ['app', ['var', 'putChar#'], ['var', 'ch#']]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['putStrLn'] = {\n\
\  expr: ['lam', 'str', ['lam', 's', ['app', ['app', ['var', 'str'], ['app', ['app', ['var', 'putChar#'], ['dat', String.fromCharCode(10)]], ['var', 's']]], ['lam', 'ch', ['lam', 'str-', ['app', ['app', ['app', ['var', 'putChar'], ['var', 'ch']], ['var', 's']], ['lam', 's1', ['lam', '_', ['app', ['app', ['var', 'putStrLn'], ['var', 'str-']], ['var', 's1']]]]]]]]]],\n\
\  env: env\n\
\};\n\
\\n\
\env['getLine'] = {\n\
\  expr: ['int', 'getLine', 1, function(s, cb){\n\
\    var go = function(){\n\
\      var take, match;\n\
\      if( match = input_buffer.match(/(^[^\\n]*)\\n((?:a|[^a])*)$/) ){\n\
\        take = match[1];\n\
\        input_buffer = match[2];\n\
\      }\n\
\      else if( input_eof ){\n\
\        if( input_buffer.length ){\n\
\          take = input_buffer;\n\
\          input_buffer = '';\n\
\        }\n\
\        else\n\
\          throw 'getLine: eof';\n\
\      }\n\
\      else{\n\
\        input_wait = function(){\n\
\          var res = go();\n\
\          if( res ){\n\
\            input_wait = null;\n\
\            cb(res);\n\
\          }\n\
\        };\n\
\        return;\n\
\      }\n\
\      var res = js_str_to_lc_str(take);\n\
\      return {expr: ['lam', 'p', ['app', ['app', ['var', 'p'], s], res.expr]], env: res.env};\n\
\    };\n\
\\n\
\    return go();\n\
\  }],\n\
\  env: env\n\
\};\n"

genRun :: IsString a => a
genRun = "if( run(['var', 'main'], env, function(){ console.log('done. (async)') }) )\n\
\  console.log('done. (sync)');\n"

srcPrelude :: IsString a => a
srcPrelude = "{-# LANGUAGE GADTs, KindSignatures, MagicHash #-}\n\
\module Prelude where\n\
\\n\
\--import Prelude (undefined)\n\
\--import GHC.Prim\n\
\\n\
\data Bool :: * where\n\
\  False :: Bool\n\
\  True :: Bool\n\
\\n\
\data Int :: * where\n\
\  I# :: Int# -> Int\n\
\\n\
\data Char :: * where\n\
\  C# :: Char# -> Char\n\
\\n\
\data Either :: * -> * -> * where\n\
\  Left :: a -> Either a b\n\
\  Right :: b -> Either a b\n\
\\n\
\data Maybe :: * -> * where\n\
\  Nothing :: Maybe a\n\
\  Just :: a -> Maybe a\n\
\\n\
\-- [a] 略略\n\
\\n\
\(++) = \\as bs -> case as of\n\
\  [] -> bs\n\
\  (:) a as -> (:) a ((++) as bs)\n\
\\n\
\take = \\n ls -> case n of\n\
\  0 -> []\n\
\  _ -> case ls of\n\
\    [] -> []\n\
\    (:) a as -> a : take (n - 1) as\n\
\\n\
\(+) = \\a b -> case a of\n\
\  I# a# -> case b of\n\
\    I# b# -> I# ((+#) a# b#)\n\
\\n\
\(-) = \\a b -> case a of\n\
\  I# a# -> case b of\n\
\    I# b# -> I# ((-#) a# b#)\n\
\\n\
\(<=) = \\a b -> case a of\n\
\  I# a# -> case b of\n\
\    I# b# -> case (<=#) of\n\
\      0# -> False\n\
\      _ -> True\n\
\\n\
\div = \\a b -> case a of\n\
\  I# a# -> case b of\n\
\    I# b# -> I# (quotInt# a# b#)\n\
\\n\
\mod = \\a b -> case a of\n\
\  I# a# -> case b of\n\
\    I# b# -> I# (remInt# a# b#)\n"

