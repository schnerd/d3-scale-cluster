const native = require('../src/ckmeans-native');
const assert = require('assert');
for (let i = 1; i < 6; i++) {
  const domain = [];
  for (let j = 0; j < 10 ** i; j++) {
    domain[j] = Math.random() * 100;
  }
  const array = new Float64Array(domain);
  console.time(`Benchmarking length ${10 ** i}`);
  const result = native.ckmeans(array, 5);
  console.timeEnd(`Benchmarking length ${10 ** i}`);
  assert.equal(result.length, 5);
}
