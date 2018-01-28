const native = require('../src/ckmeans-native')
// const input = [1, 2, 4, 5, 12, 43, 52, 123, 234, 1244]
const input = [ 66, 85, 39, 52, 10, 71, 18, 69, 65, 82, 54, 93, 24, 37, 54, 83, 82, 13, 20, 23, 92, 51, 15, 41, 0, 18, 60, 60, 58, 19, 31, 1, 34, 1, 44, 45, 81, 7, 84 ]
console.log(native(input, 5))
