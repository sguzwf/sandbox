//var util = require('./ULC-util.js');
//var pretty_closure = util.pretty_closure;

//var fs = require('fs');

function clone_env(env){
  var ctor = new Function;
  ctor.prototype = env;
  return new ctor;
}

function clone_array(array){
  var out = new Array(array.length), i;
  for(i=0; i<array.length; ++i)
    out[i] = array[i];
  return out;
}

function weak_normal_form(closure, cb){
  //console.log('weak_normal_form');
  //console.log(pretty_closure(closure, 1));
  var lam, env2, new_lam, new_closure, app_cont;
  switch(closure.expr[0]){
    case 'dat':
      return closure;

    case 'var':
      if( closure.env[closure.expr[1]] ){
        new_closure = weak_normal_form(closure.env[closure.expr[1]], cb);
        if( !new_closure )
          return;
        closure.env = new_closure.env;
        closure.expr = new_closure.expr;
      }
      return closure;

    case 'lam':
      return closure;

    case 'app':
      app_cont = function(lam){
        if( lam.expr[0]==='int' ){
          new_lam = {
            expr: clone_array(lam.expr),
            env: lam.env
          };
          --new_lam.expr[2];
          new_lam.expr.push({expr: closure.expr[2], env: closure.env});
          new_closure = weak_normal_form(new_lam, cb);
          if( !new_closure )
            return;
        }
        else if( lam.expr[0]==='lam' ){
          env2 = clone_env(lam.env);
          env2[lam.expr[1]] = {expr: closure.expr[2], env: closure.env};
          new_closure = weak_normal_form({expr: lam.expr[2], env: env2}, cb);
          if( !new_closure )
            return;
        }
        else{
          throw 'non-appable app: ' + JSON.stringify(lam.expr);
        }
        closure.env = new_closure.env;
        closure.expr = new_closure.expr;
        return closure;
      };

      lam = weak_normal_form({expr: closure.expr[1], env: closure.env}, function(lam){
        var res = app_cont(lam);
        if( res )
          cb(res);
      });
      if( lam )
        return app_cont(lam);
      else
        return;

    case 'int':
      if( closure.expr[2]===0 ) {
        new_closure = closure.expr[3].apply(closure.env, closure.expr.slice(4).concat([cb]));
        if( !new_closure )
          return;
        closure.env = new_closure.env;
        closure.expr = new_closure.expr;
      }
      return closure;
  }
}

var input_buffer = '';
var input_eof = false;
var input_wait = null;

function run(expr, env, done){
  var i;

  var cont = function(res){ // continuation?
    res = weak_normal_form(res, cont);
    if( res )
      done(res);
  };
  return weak_normal_form({expr: ['app', expr, null], env: env}, cont);
}

var env = {};
