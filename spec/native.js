const native = require('../src/ckmeans-native')
const array = new Float64Array(5)
console.log(native.ckmeans(array, 5))
