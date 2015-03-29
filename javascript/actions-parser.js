#!/usr/bin/env node
var esprima = require('esprima');
var estraverse = require('estraverse');
var escodegen = require('escodegen');
var fs = require('fs');
var _ = require('lodash');

var file = fs.readFileSync('./actions.js', 'utf-8');
var tree = esprima.parse(file);

var copyDeclaration = function copyDeclaration(result, node) {
  var found, logNode;

  if (node.type === 'VariableDeclaration') {
    found = false;
    found = node.declarations.reduce(
      function(result, node) {
        var arg;

        if (
          /.*Actions/.test(node.id.name) &&
          node.init.type === 'CallExpression' &&
          node.init.callee.name === 'require'
        ) {
          logNode = _.cloneDeep(node);
          logNode.id.name = 'LogActions$';
          arg = logNode.init.arguments[0];
          arg.value = arg.value.replace(node.id.name, 'LogActions$');
          arg.raw   = arg.raw.replace(node.id.name, 'LogActions$');
          return result || true;
        }
        return result || false;
      },
      false
    );

    if (found) {
      node.declarations.push(logNode);
    }
  }

  result.push(node);
  return result;
};

var copyCall = function copyCall(result, node) {
  var logNode;

  result.push(node);

  if (
    node.type === 'ExpressionStatement' &&
    node.expression.type === 'CallExpression' &&
    node.expression.callee.type === 'MemberExpression' &&
    /.*Actions/.test(node.expression.callee.object.name)
  ) {
    logNode = _.cloneDeep(node);
    logNode.expression.callee.object.name = 'LogActions$';
    result.push(logNode);
  }

  return result;
};

var newTree = estraverse.replace(tree, {
  enter: function enter(node, parent) {
    if (
      node.type === 'Program' ||
      node.type === 'BlockStatement'
    ) {
      node.body = node.body.reduce(copyDeclaration, []);
      node.body = node.body.reduce(copyCall, []);
    }
  },
});

console.log(escodegen.generate(newTree));

