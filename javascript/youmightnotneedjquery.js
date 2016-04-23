// http://youmightnotneedjquery.com/ as code kata

/******************************
 * AJAX
 ******************************/

// JSON - IE9+
var request = new XMLHttpRequest();
request.open('GET', '/my/url', true);

request.onload = function() {
  if( requset.status >= 200 && request.status < 400 )
    var data = JSON.parse(request.responseText);
  else
    console.error('server error');
};

request.onerror = function() {
  console.error('connection error');
};

request.send();



// Post - IE8+
var request = new XMLHttpRequest();
request.open('POST', 'my/url', true);
request.setRequestHeader('Content-Type', 'application/x-www-form-urlencode; chareset=UTF-8');
request.send(data);



// Request - IE9+
var request = new XMLHttpRequest();
request.open('GET', '/my/url', true);

request.onload = function() {
  if( request.status >= 200 && request.status < 400)
    var resp = request.responseText;
  else
    console.error('server error');
};

request.onerror = function() {
  console.error('connection error');
};

request.send();



/******************************
 * Effects
 ******************************/

// Fade In - IE9+
function fadeIn(el) {
  el.style.opacity = 0;

  var last = +new Date();
  var tick = function() {
    el.style.opacity = el.style.opacity + (new Date() - last) / 400;
    last = +new Date();

    if( +el.style.opacity < 1 )
      (window.requestAnimationFrame && window.requestAnimationFrame(tick)) || setTimeout(tick, 16);
  };

  tick();
}

fadeIn(el);



// Hide - IE8+
el.style.display = 'none';



// Show - IE8+
el.style.display = '';



/******************************
 * Elements
 ******************************/

// Add Class - IE8+
if( el.classList )
  el.classList.add(className)
else
  el.className += ' ' + className



// After - IE8+
el.insertAdjacentHTML('afterend', htmlString);



// Append - IE8+
parent.appendChild(er);



// Before - IE8+
el.insertAdjacentHTML('beforebegin', htmlString);



// Children - IE9+
el.children;



// Clone - IE8+
el.cloneNode(true);



// Contains - IE8+
el !== child && el.contains(child);



// Contains Selector - IE8+
el.querySelector(selector) !== null;



// Each - IE9+
var elements = document.querySelectorAll(selector);
Array.prototype.forEach.call(elements, function(el, i) {
  console.log(el, i);
});



// Empty - IE9+
el.innerHTML = '';



// Filter - IE9+
Array.prototype.filter.call(document.querySelectorAll(selector), filterFn);



// Find Children - IE8+
el.querySelectorAll(selector);



// Find Elements - IE8+
document.querySelectorAll('.my #awesome selector');



// Get Attributes - IE8+
el.getAttribute('tabindex');



// Get Html - IE8+
el.innerHTML;



// Get Outer Html - IE8+
el.outerHTML;



// Get Style - IE9+
getComputedStyle(el)[ruleName];



// Get Text - IE9+
el.textContent;



// Has Class - IE8+
if( el.classList )
  el.classList.contains(className);
else
  new RegExp('(^| )' + className + '( |$)', 'gi').test(el.className);



// Matches - IE8+
el === otherEl;



// Matches Selector - IE9+
var matches = function(el, selector) {
  return (el.matches || el.matchesSelector || el.msMatchesSelector || el.mozMatchesSelector || el.webkitMatchesSelector || el.oMatchesSelector).call(el, selector);

matches(el, '.my-class');



// Next - IE9+
el.nextSibling;



// Offset - IE8+
var rect = el.getBoundingClientRect();

{
  top: rect.top + document.body.scrollTop,
  left: rect.left + document.body.scrollLeft
};



// Offset Parent - IE8+
el.offsetParent || el;



// Outer Height - IE8+
el.offsetHeight;



// Outer Height with Margin - IE9+
function outerHeight(el) {
  var height = el.offsetHeight;
  var style = getComputedStyle(el);

  height += parseInt(style.marginTop) + parseInt(style.marginBottom);
  return height;
}

outerHeight(el);



// Outer Width - IE8+
el.offsetWidth;



// Outer Width with Margin - IE9+
function outerWidth(el) {
  var width = el.offsetWidth;
  var style = getComputedStyle(el);

  width += parseInt(style.marginLeft) + parseInt(style.marginRight);
  return width;
}

outerWidth(el);



// Parent - IE8+
el.parentNode;



// Position - IE8+
{left: el.offsetLeft, top: el.offsetTop};



// Position Relative to Viewport
el.getBoundingClientRect();



// Prepend - IE8+
parent.insertBefore(el, parent.firstChild);



// Prev - IE9+
el.previousElementSibling;



// Remove - IE8+
el.parentNode.removeChild(el);



// Remove Class - IE8+
if( el.classList )
  el.classList.remove(className);
else
  el.className = el.className.replace(new RegExp('(^|\\b)' + className.split(' ').join('|') + '(\\b|$)', 'gi'), ' ');



// Replace from Html - IE8+
el.outerHTML = string;



// Set Attributes - IE8+
el.setAttribute('tabindex', 3);



// Set Html - IE8+
el.innerHtml = string;



// Set Style - IE8+
el.style.borderWidth = '20px';



// Set Text - IE9+
el.textContent = string;



// Siblings - IE9+
Array.prototype.filter.call(el.parentNode.children, function(child) {
  return child !== el;
});



// Toggle Class - IE9+
if( el.classList )
  el.classList.toggle(className);
else {
  var classes = el.className.split(' ');
  var existingIndex = classes.indexOf(className);

  if( existingIndex >= 0 )
    class.splice(existingIndex, 1);
  else
    classes.push(className);

  el.className = classes.join(' ');
}



/******************************
 * Events
 ******************************/

// Off - IE9+
el.removeEventListener(eventName, eventHandler);



// On - IE9+
el.addEventListener(eventName, eventHandler);



// Ready - IE9+
function ready(fn) {
  if( document.readyState != 'loading' )
    fn();
  else
    document.addEventListener('DOMContentLoaded', fn);
}



// Trigger Custom - IE9+
if( window.CustomEvent )
  var event = new CustomEvent('my-event', {detail: {some: 'data'}});
else {
  var event = document.createEvent('CustomEvent');
  event.initEvent('my-event', true, true, {some: 'data'});
}

el.dispatchEvent(event);



// Trigger Native - IE9+
var event = document.createEvent('HTMLEvents');
event.initEvent('change', true, false);
el.dispatchEvent(event);



/******************************
 * Utils
 ******************************/

// Bind - IE9+
fn.bind(context);



// Array Each - IE9+
array.forEach(function(item, i) {
});



// Deep Extend - IE6+
var deepExtend = function(out) {
  out = out || {};

  for (var i = 1; i < arguments.length; ++i) {
    var obj = arguments[i];

    if( !obj )
      continue;

    for (var key in obj)
      if( obj.hasOwnProperty(key) )
        if( typeof obj[key] === 'object' )
          out[key] = deepExtend(out[key], obj[key]);
        else
          out[key] = obj[key];
  }

  return out;
};

deepExpend({}, objA, objB);



// Extend - IE8+
var extend = function(out) {
  out = out || {};

  for (var i = 1; i < arguments.length; ++i) {
    if( !arguments[i] )
      continue;

    for (var key in arguments[i])
      if( arguments[i].hasOwnProperty(key) )
        out[key] = arguments[i][key];
  }

  return out;
};



// Index Of - IE9+
array.indexOf(item);



// Is Array - IE9+
Array.isArray(arr);



// Map - IE9+
array.map(function(value, index) {
});



// Now - IE9+
Date.now();



// Parse HTML - IE9+
var parseHTML = function(str) {
  var tmp = document.implementation.createHTMLDocument();
  tmp.body.innerHTML = str;
  return tmp.body.children;
};

parseHTML(htmlString);



// Parse Json - IE8+
JSON.parse(string);



// Trim - IE9+
string.trim();



// Type - IE8+
Object.prototype.toString.call(obj).replace(/^\[object (.+)\]$/, '$1').toLowerCase();
