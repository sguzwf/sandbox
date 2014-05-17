var Task,
    Promise,
    ListPromise,
    util = require("util"),
    fs = require("fs"),
    readdir,
    stat,
    slice;

slice = Array.prototype.slice;

Promise = function() {
  var resolved = false,
      observers = [],
      args;

  this.then = function(func) {
    if (resolved && typeof func === "function") {
      func.apply(this, args);
    }
    observers.push(func);
  };

  this.resolve = function() {
    resolved = true;
    args = slice.apply(arguments);
    observers.forEach(function(func) {
      if (typeof func === "function") {
        func.apply(this, args);
      }
    });
  };

  this.reject = function(err) {
    console.log(err);
  };
};

Promise.create = function(that, action) {
  return function() {
    var p  = new Promise,
        args = slice.apply(arguments);
    args.push(function() {
      var results = slice.apply(arguments);
      if(results[0] !== null) {
        p.reject(results[0]);
      } else {
        results.shift();
        p.resolve.apply(p, results);
      }
    });
    action.apply(that, args);
    return p;
  };
};

Promise.all = function() {
  var p = new Promise,
      results = [],
      promises = slice.apply(arguments);

  if (Array.isArray(promises[0])) {
    promises = promises[0];
  }

  (promises.reduceRight(
    function(next, promise) {
      return function () {
        promise.then(function(result) {
          results.push(result);
          next();
        });
      }
    },
    function() { p.resolve(results); }
  )());

  return p;
};

readdir = Promise.create(fs, fs.readdir);
stat = Promise.create(fs, fs.stat);
readdir("./")
  .then(function(files) {
    Promise
      .all(
        files.map(function(file) {
          return stat(file);
        })
      )
      .then(console.log);
  });
