const native = require('../src/ckmeans-native')
const input = [1, 2, 4, 5, 12, 43, 52, 123, 234, 1244]
const array = new Float64Array(input)

console.log(native.ckmeans(array, 5))
console.log(array)
