/* globals describe, beforeEach, afterEach, it, expect */
var sinon = require('sinon');
var ckmeansNative = require('../src/ckmeans-native');
var d3scaleCluster = require('../src/index.js');

describe('Napi ckmeans', function () {
  var sandbox;
  var scale;
  var DEFAULT_RANGE = ['a', 'b', 'c', 'd', 'e', 'f'];

  beforeEach(function () {
    scale = d3scaleCluster();
  });
  beforeEach(function () {
    sandbox = sinon.sandbox.create();
  });
  afterEach(function () {
    sandbox.restore();
  });

  it('It should call native api for big arrays', function () {
    sandbox.spy(ckmeansNative, 'ckmeans');
    const bigArray = new Array(1000);

    for (var i = 0; i < 2000; i++) {
      bigArray[i] = Math.random();
    }
    scale
      .domain(bigArray)
      .range(DEFAULT_RANGE);
    expect(scale(0.1)).toEqual('a');
    expect(ckmeansNative.ckmeans.called).toBe(true);
  });
});
