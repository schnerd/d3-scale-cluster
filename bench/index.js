const ckmeans = require('../src/ckmeans');
const assert = require('assert');
for (let i = 1; i < 6; i++) {
  const domain = [];
  for (let j = 0; j < 10 ** i; j++) {
    domain[j] = Math.random();
  }
  console.time(`Benchmarking length ${10 ** i}`);
  const result = ckmeans(domain, 5);
  console.timeEnd(`Benchmarking length ${10 ** i}`);
  assert.equal(result.length, 5);
}
