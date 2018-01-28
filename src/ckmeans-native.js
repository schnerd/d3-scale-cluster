const nativeCkmeans = require('bindings')('ckmeans')
function ckmeans (data, nClusters) {
  const array = new Float64Array(data)

  return nativeCkmeans.ckmeans(array, nClusters)
}

module.exports = ckmeans
