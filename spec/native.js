const native = require('../src/ckmeans-native')
const input = [2, 3, 4, 1, 0]
const array = new Float64Array(input)

console.log(native.ckmeans(array, 5))
console.log(array)
