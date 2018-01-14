const d3scaleCluster = require('../src')
const assert = require('assert')
for (let i = 0; i < 6; i++) {
  const domain = []
  const DEFAULT_RANGE = ['a', 'b', 'c', 'd', 'e', 'f'];
  for (let j = 0; j < 10 ** i; j ++) {
    domain[j] = Math.random()
  }
  const scale = d3scaleCluster()
  scale.domain(domain)
  console.time(`Benchmarking length ${10 ** i}`)
  scale.range(DEFAULT_RANGE)
  console.timeEnd(`Benchmarking length ${10 ** i}`)
  assert.equal(scale(0.01), 'a')
}