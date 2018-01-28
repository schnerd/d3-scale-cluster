var nativeCkmeans = require('bindings')('ckmeans')
function ckmeans (data, nClusters) {
  var array = new Float64Array(data)

  return nativeCkmeans.ckmeans(array, nClusters)
}

exports.ckmeans = ckmeans
