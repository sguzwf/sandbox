var svg = document.querySelector('svg');
// XXX: 這鬼東西竟然真是當 global var 用...
var root = {
  dom: svg,
  x: 0,
  y: 0
};

// 1 //
var newNode = function(tagName){
  return document.createElementNS("http://www.w3.org/2000/svg", tagName);
};

// 3 //
var newTextNode = function(str){
  return document.createTextNode(str);
};

// 2 //
var newText = function(x, y, str, p){
  // XXX: 如果是我，一定傻到開始想做 world matrix
  var text = {
    x: x + p.x,
    y: y + p.y
  };
  var dom = newNode('text');
  dom.setAttribute('x', text.x);
  dom.setAttribute('y', text.y);
  dom.setAttribute('text-anchor', 'middle');
  dom.setAttribute('alignment-baseline', 'middle');
  dom.appendChild(newTextNode(str));
  text.dom = dom;
  svg.appendChild(dom);
  return text;
};

// 0 //
// XXX: p 看來是 parent
var newBox = function(x, y, w, h, level, p, opts) {
  if( !opts )
    opts = {};
  var box = {
    x: x + p.x,
    y: y + p.y,
    w: w,
    h: h
  };
  var i;
  var dom = [];
  for(i=0; i<level; ++i){
    dom.push(newNode('rect'));
    dom[i].setAttribute('x', box.x);
    dom[i].setAttribute('y', box.y + h/level*i); // XXX: ???
    dom[i].setAttribute('width', w);
    dom[i].setAttribute('height', h/level);
    dom[i].setAttribute('stroke', opts.stroke || '#000');
    dom[i].setAttribute('fill', opts.fill || 'transparent');
    dom[i].setAttribute('stroke-width', opts.strokeWidth || 2);
    if( opts.text && opts.text[i] )
      // XXX: 和 text 有關？
      newText(box.w/2, (h/level>=40 ? h/level*i+20 : h/level*(i+0.5)), opts.text[i], box);
    svg.appendChild(dom[i]);
  }
  box.dom = dom;

  box.link = [
    // XXX: distance to what? to the center
    // XXX: you do write your own function sqr, don't you?
    {x: box.x, y: box.y, d: Math.sqrt(box.w*box.w+box.h*box.h)/2},
    {x: box.x+box.w/2, y: box.y, d: box.h/2},
    {x: box.x+box.w, y: box.y, d: Math.sqrt(box.w*box.w+box.h*box.h)/2},
    {x: box.x+box.w, y: box.y+box.h/2, d: box.w/2},
    {x: box.x+box.w, y: box.y+box.h, d: Math.sqrt(box.w*box.w+box.h*box.h)/2},
    {x: box.x+box.w/2, y: box.y+box.h, d: box.h/2},
    {x: box.x, y: box.y+box.h, d: Math.sqrt(box.w*box.w+box.h*box.h)/2},
    {x: box.x, y: box.y+box.h/2, d: box.w/2}
  ];

  return box;
};

var world = newBox(450, 10, 100, 590, 1, root, {text: ['real world']});
