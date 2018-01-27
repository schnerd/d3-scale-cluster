const native = require('../src/ckmeans-native')
const assert = require('assert')
for (let i = 0; i < 6; i++) {
  const domain = []
  const DEFAULT_RANGE = ['a', 'b', 'c', 'd', 'e', 'f'];
  for (let j = 0; j < 10 ** i; j++) {
    domain[j] = Math.random() * 100
  }
  const array = new Float64Array(domain)
  console.time(`Benchmarking length ${10 ** i}`)
  const result = native.ckmeans(array, 5)
  console.timeEnd(`Benchmarking length ${10 ** i}`)
  console.log(result)
}
