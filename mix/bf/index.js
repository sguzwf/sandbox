// Generated by LiveScript 1.2.0
(function(){
  var $, Brainfuck;
  $ = require('jquery');
  Brainfuck = require('./bf');
  $.get('./hello.bf', function(data){
    var x$, bf;
    x$ = bf = Brainfuck();
    x$.output = function(it){
      return document.write(it);
    };
    x$.exec(data);
    return x$;
  });
}).call(this);
