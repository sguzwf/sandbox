'use strict';

var _clone = require('lodash.clone');

function _joinClasses(classes) {
  return Array.isArray(classes) ? classes.join(' ') :
    typeof classes == 'string' ? classes : null;
}

function _joinStyleValues(style) {
  if (typeof style == 'string') {
    return style;
  }
  var strs = [];
  Object.keys(style).forEach(k => {
    strs.push(k + ': ' + style[k]);
  });
  return strs.join('; ');
}

function _joinAttributes(attributes) {
  var strs = [];
  Object.keys(attributes).forEach(k => {
    strs.push(' ' + k + '="' + attributes[k] + '"');
  });
  return strs.join('');
}

function _setAttributeOnMap(map, key, value) {
  if (value === undefined || value === null) {
    return;
  }
  map[key] = '' + value;
}

function _setAttributeOnDOM(element, key, value) {
  if (!element) {
    return;
  }
  if (value === undefined || value === null) {
    element.removeAttribute(key);
  } else {
    element.setAttribute(key, '' + value);
  }
}

function _setAttributes(setter, key, value) {
  if (value !== null && typeof value == 'object') {
    Object.keys(value).forEach(k => {
      _setAttributes(setter, key ? (key + '-' + vk) : vk, value[vk]);
    });
  } else {
    setter(key, value);
  }
}



var tagPass = {
  reconcile: (reconciler, element, state) => {
    delete state.tag;
  },
  stringify: (reconciler, obj, state) => {
    obj.tag = state.tag || 'div';
    delete state.tag;
  }
};

var childrenPass = {
  reconcile: (reconciler, element, state) => {
    if (state.children == null) return;
    element.innerHTML = reconciler.stringify(state.children);
    delete state.children;
  },
  stringify: (reconciler, obj, state) => {
    obj.children = state.children != null ? reconciler.stringify(state.children) : '';
    delete state.children;
  }
};

var classesPass = {
  reconcile: (reconciler, element, state) => {
    if (state.classes == null) return;
    element.className = _joinClasses(state.classes);
    delete state.classes;
  },
  stringify: (reconciler, obj, state) => {
    if (state.classes == null) return;
    obj.attributes['class'] = _joinClasses(state.classes);
    delete state.classes;
  }
};

var stylePass = {
  reconcile: (reconciler, element, state) => {
    if (state.style == null) return;
    element.style = _joinStyleValues(state.style);
    delete state.style;
  },
  stringify: (reconciler, obj, state) => {
    if (state.style == null) return;
    obj.attributes.style = _joinStyleValues(state.style);
    delete state.style;
  }
}

class Reconciler {

  constructor() {
    this.passes = [tagPass, classesPass, stylePass, childrenPass];
  }

  resolve(state, ...data) {
    return typeof state == 'function' ? state(...data) : _clone(state, true);
  }

  stringify(state, ...data) {
    if (state === undefined || state === null) {
      return '';
    }
    if (typeof state == 'string') {
      return state;
    }
    state = this.resolve(state, ...data);
    if (Array.isArray(state)) {
      return state.map(s => this.stringify(s)).join('');
    }
    if (typeof state != 'object') {
      return '' + state;
    }

    var obj = { attributes: {} };
    this.passes.forEach(p => p.stringify(this, obj, state));
    _setAttributes((k, v) => _setAttributeOnMap(obj.attributes, k, v), '', state);
    return '<' + obj.tag + _joinAttributes(obj.attributes) + '>' + obj.children + '</' + obj.tag + '>';
  }

  reconcile(element, state, ...data) {
    if (state === undefined || state === null) {
      return;
    }
    if (typeof state == 'string') {
      return; // TODO: parse
    }
    state = this.resolve(state, ...data);
    if (typeof state != 'object') {
      return; // TODO: throw error
    }

    this.passes.forEach(p => p.reconcile(this, element, state));
    _setAttributes((k, v) => _setAttributeOnDOM(element, k, v), '', state);
  }

  plugin(jQuery) {
    var self = this;
    jQuery.fn.extend({
      reconcile: function(state, ...data) {
        state = self.resolve(state, ...data);
        return this.each((i, elem) => self.reconcile(elem, state));
      },
      prependx: function(state, ...data) {
        return this.prepend(self.stringify(state, ...data));
      },
      appendx: function(state, ...data) {
        return this.append(self.stringify(state, ...data));
      }
    });
  }
}

function rec() {
  return new Reconciler();
}

module.exports = rec;
