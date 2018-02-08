/* globals describe, it, expect */
const nativeCkMeans = require('../src/ckmeans-native');
const jsCkMeans = require('../src/ckmeans');
describe('Ckmeans', function () {
  it('Test they return the same', function () {
    for (let i = 0; i < 30; i++) {
      const length = parseInt(Math.random() * 10 + 300);
      const data = [];
      for (let j = 0; j < length; j++) {
        data[j] = parseInt(Math.random() * 100);
      }
      const nClusters = parseInt(Math.random() * 10) + 2;
      const native = nativeCkMeans.ckmeans([...data], nClusters);
      const js = jsCkMeans([...data], nClusters);
      expect(js).toEqual(Array.from(native), data, nClusters);
    }
  });
});
