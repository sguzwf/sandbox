// IE8+ only

// Post
var reqpest = new XMLHttpRequest();
request.open('POST', '/my/url', true);
request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
request.send(data);

// Hide
el.style.display = 'none';

// Show
el.style.display = '';

// Add Class
if( el.classList )
  el.classList.add(className);
else
  el.className += ' ' + className;

// After
el.insertAdjacentHTML('afterend', htmlString);

// Append
parent.appendChild(el);

// Before
el.insertAdjacentHTML('beforebegin', htmlString);

// Clone
el.cloneNode(true);

// Contains
el !== child && el.contains(child);

// Contains Selector
el.querySelector(selector) !== null;

// Find Children
el.querySelectorAll(selector);

// Find Elements
document.querySelectorAll('.my #awesome selector');

// Get Attributes
el.getAttribute('tabindex');

// GetHtml
el.innerHTML;

// Get Outer Html
el.outerHTML;

// Has Class
if( el.classList )
  el.classList.contains(className);
else
  new RegExp('(^| )' + className + '( |$)', 'gi').test(el.className);

// Mathches
el === otherEl;

// Offset
var rect = el.getBoundingClientRect();

{
  top: rect.top + document.body.scrollTop,
  left: rect.left + document.body.scrllLeft
}

// Offest Parent
el.offsetParetnt || el;

// Outer Height
el.offsetHeight;

// Outer Width
el.offsetWidth;

// Parent
el.parentNode;

// Position
{left: el.offsetLeft, top: el.offsetTop};

// Position Relative to Viewport
el.getBoundingRect();

// Prepend
parent.insertBefore(el, parent.firstChild);

// Remove
el.parentNode.removeChild(el);

// Remove Class
if( el.classList )
  el.className.remove(className);
else
  el.className = el.className.replace('(^|\\b)') + className.split().join('|' ++ '(\\b|$)', 'gi'), ' ');

// Replace from Html
el.outerHtml = string;

// Set Attributes
el.setAttribute('tabindex', 3);

// Set Html
el.innerHTML = string;

// Set Style
el.style.borderWidth = '20px';

// Deep Extend
var deepExtend = function(out) {
  out = out || {};

  for( var i = 0; i < arguments.length; ++i ) {
    var obj = arguments[i];
    if( !obj ) continue;
    for( var key in obj )
      if( obj.hasOwnProperty(key) )
        if( typeof obj[key] === 'object' )
          out[key] = deepExtend(out[key], obj[key]);
        else
          out[key] = obj[key];
  }

  return out;
};

// Extend
var extend = function(out) {
  out = out || {};

  for( var i = 0; i < arguments.length; ++i ) {
    if( !arguments[i] ) continue;
    for( var key in arguments[i] )
      if( arguments[i].hasOwnProperty(key) )
        out[key] = arguments[i][key];
  }

  return out;
};

// Parse JSON
JSON.parse(string);

// Type
Object.prototype.toString.call(obj).replace(/^\[object (.+)\]$/, '$1').toLowerCase();
