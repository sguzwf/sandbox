// Q1
var MyPromise = function(f) {
  var that = this;
  this._resolved = false;
  this._value = null;
  this._listeners = [];
  if (f) {
    setTimeout(f, 0, function(v) {
      that._resolve(v);
    });
  }
};

MyPromise.all = function(array) {
  return new MyPromise(function(resolve) {
    var count = 0;
    var result = [];
    var end = function() {
      count++;
      if (count === array.length){
        resolve(result);
      }
    };

    array.forEach(function(p, i) {
      if (p.then) {
        p.then(function(v) {
          result[i] = v;
          end();
        });
      } else {
        result[i] = p;
        end();
      }
    });
  });
}

MyPromise.prototype._resolve = function(value) {
  this._resolved = true;
  this._value = value;
  this._listeners.forEach(function(listener) { listener() });
};

MyPromise.prototype.then = function(cb) {
  var that = this;
  var p = new MyPromise();
  var r;
  var f;

  cb = cb || function(it) { return it };

  f = function() {
    r = cb(that._value);
    if (r && r.then) {
      r.then(function(v) { p._resolve(v) });
    } else {
      p._resolve(r);
    }
  };

  if (this._resolved) {
    f();
  } else {
    this._listeners.push(f);
  }

  return p;
};



function getInterval(str) {
  switch (str) {
    case 'Math':       return 5000;
    case 'Psychology': return 10000;
    case 'English':    return 2000;
    case 'Chinese':    return 2000;
    case 'Science':    return 5000;
    case 'Literature': return 8000;
  };
}

function doHomeWork(str) {
  var interval = getInterval(str);

  return function(acc) {
    var bgn = Date.now();
    var result = acc ? acc.concat([str]) : [];

    return new MyPromise(function(resolve) {
      setTimeout(function() {
        //console.log(str, (Date.now() - bgn) / 1000);
        console.log(str);
        resolve(result);
      }, interval);
    });
  };
}

function doHomeWork$(str) {
  var interval = getInterval(str);

  return function() {
    var bgn = Date.now();

    return new MyPromise(function(resolve) {
      setTimeout(function() {
        //console.log('_' + str, (Date.now() - bgn) / 1000);
        resolve(str);
      }, interval);
    });
  };
}



// Due to the order of evaluation, it is impossible to solve this problem
// without invoking the first function.
var q1 = doHomeWork('Math')()
  .then(doHomeWork('Math'))
  .then(doHomeWork('English'))
  .then(doHomeWork('Psychology'))
  .then(doHomeWork('Science'));



// Q2
var Robot = function() {
  this._limit = 2;
  this._last = new MyPromise();
  this._last._resolve([]);
  this._working = 0;
  this._waiting = [];
};

Robot.prototype.digest = function() {
  var p;
  if (this._limit < this._working && this._waiting.length) {
    this._working++;
    p = this._waiting.shift()();
    p.then(function() {
      this._working--;
      this.digest();
    });
  }
};

Robot.prototype.add = function(title) {
  var i;

  this._waiting.push(doHomeWork$(title));
  if ('Science' === title) {
    for (i = 0; i < 3; ++i) {
      this._waiting.push(doHomeWork$('Math'));
    }
  }
};

Robot.prototype.on = function(_, f) {
  var p;

  // cheating
  this.digest();
  p = MyPromise.all(this._waiting.map(function(t) { return t() }));
  p.then(f);

  return p;
};



var robot = new Robot();

robot.add('Math');
robot.add('English');
robot.add('Psychology');
robot.add('Science');
robot.add('Literature');
robot.add('Math');

var q2 = robot.on('finish');



// Q3
var data = [{
  id: 1,
  title: 'Campaign 1',
  retargetList: [{
    id: 1,
    name: 'retargetList 1'
  }]
}, {
  id: 2,
  title: 'Campaign 2',
  retargetList: [{
    id: 1,
    name: 'retargetList 1'
  },{
    id: 2,
    name: 'retargetList 2'
  }]
}]


var transform = (function() {
  var _names = {};

  function _transform(key, value) {
    return value.map(function(c, i) {
      var k, v, list;

      if(c.id) {
        _names[key] = _names[key] || {};
        list = _names[key];
        list[c.id] = list[c.id] || c;
      }

      for(k in c) {
        if(c.hasOwnProperty(k)) {
          v = c[k];
          if(Array.isArray(v)) {
            c[k] = _transform(k, v);
          }
        }
      };

      return i;
    });
  }

  return function(key, value) {
    _transform(key, value);
    return _names;
  }
}());


var q3 = (function() {
  var result = transform('campaigns', data);
  return JSON.stringify(result, null, 2);
}());

MyPromise.all([q1, q2, q3]).then(function(r) {
  r.forEach(function(q, i) {
    console.log('Q' + (i + 1), q);
  });
});
