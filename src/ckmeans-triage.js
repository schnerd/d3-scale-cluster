var jsCkmeans = require('./ckmeans');
var nativeCkMeans;
if (typeof process !== 'undefined' && process && process.version && parseInt(process.version.substr(1, 1)) >= 8) {
  nativeCkMeans = require('./ckmeans-native');
  module.exports = function (data, nClusters) {
    if (data.length > 200 && nClusters < data.length && nClusters > 1) {
      return nativeCkMeans.ckmeans(data, nClusters);
    } else {
      return jsCkmeans(data, nClusters);
    }
  };
} else {
  module.exports = jsCkmeans;
}
