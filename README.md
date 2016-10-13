# d3-scale-cluster

D3 scale that clusters data into discrete groups. Similar to [quantile scales](https://github.com/d3/d3-scale/blob/master/README.md#scaleQuantile), the cluster scale maps a sampled input domain to a discrete range. The number of values in the output range determines the number of clusters that will be computed from the domain. The graphic below demonstrates how cluster compares to d3's quantile and quantize scales:

<img width="420" alt="d3 scale cluster example" src="https://cloud.githubusercontent.com/assets/875591/18608070/0213d7ce-7cdf-11e6-89aa-1b0e18e63cc8.png">

Clusters are computed using a 1-dimensional clustering algorithm with an `O(kn log(n))` runtime (where `k` is the number of clusters desired). This should be fast enough for the majority of projects, but it's worth doing your own performance testing when working with large data sets. More details about the algorithm can be found later in this document.  

To use this scale, you may install via npm:
```
npm install d3-cluster-scale
```

Or include a `<script>` tag on your page after d3
```
<script src="https://unpkg.com/d3-scale-cluster@1.1.2/dist/d3-scale-cluster.min.js"></script>
```

###Example Usage

This scale largely has the same API as [d3.scaleQuantile](https://github.com/d3/d3-scale/blob/master/README.md#scaleQuantile) (however we use `clusters()` instead of `quantiles()`)

```js
var scale = d3.scaleCluster()
    .domain([1, 2, 4, 5, 12, 43, 52, 123, 234, 1244])
    .range(['#E5D6EA', '#C798D3', '#9E58AF', '#7F3391', '#581F66', '#30003A']);

var clusters = scale.clusters(); // [12, 43, 123, 234, 1244]
var color = scale(52); // '#9E58AF'
var extent = scale.invertExtent('#9E58AF'); // [43, 123]
```

###API

d3.**scaleCluster**()

Constructs a new cluster scale with an empty domain and an empty range. The cluster scale is invalid until both a domain and range are specified.

_cluster_(_value_)

Given a value in the input domain, returns the corresponding value in the output range.

_cluster_.**invertExtent**(_value_)

Returns the extent of values in the domain [x0, x1] for the corresponding value in the range: the inverse of cluster. This method is useful for interaction, say to determine the value in the domain that corresponds to the pixel location under the mouse.

_cluster_.**domain**(_[domain]_)

If domain is specified, sets the domain of the quantile scale to the specified set of discrete numeric values. The array must not be empty, and must contain at least one numeric value; NaN, null and undefined values are ignored and not considered part of the sample population. If the elements in the given array are not numbers, they will be coerced to numbers. A copy of the input array is sorted and stored internally. If domain is not specified, returns the scale’s current domain.

_cluster_.**range**(_[range]_)

If range is specified, sets the discrete values in the range. The array must not be empty, and may contain any type of value. The number of values in (the cardinality, or length, of) the range array determines the number of clusters that are computed. If range is not specified, returns the current range.

_cluster_.**clusters**()

Returns the cluster thresholds. If the range contains n discrete values, the returned array will contain n - 1 thresholds. Values less than the first threshold are considered in the first cluster; values greater than or equal to the first threshold but less than the second threshold are in the second cluster, and so on.

_cluster_.**copy**()

Returns an exact copy of this scale. Changes to this scale will not affect the returned scale, and vice versa.

###The Algorithm / History

For clustering, this project uses the [Ckmeans](http://simplestatistics.org/docs/#ckmeans) algorithm implementation from the [simple-statistics](https://github.com/simple-statistics/simple-statistics) library (the original algorithm was designed by [Haizhou Wang and Mingzhou Song](https://cran.r-project.org/web/packages/Ckmeans.1d.dp/)). This algorithm is a major improvement on the [Jenks Natural Breaks](https://en.wikipedia.org/wiki/Jenks_natural_breaks_optimization) algorithm developed by cartographer George Jenks. Tom MacWright wrote previously about [using Jenks Natural Breaks for d3 choropleths](http://www.macwright.org/2013/02/18/literate-jenks.html), but to my knowledge it was never turned into a reusable d3 scale.

As noted previously in this document, the Ckmeans algorithm has a runtime complexity of  `O(kn log(n))`, where `k` is the number of clusters. Here's a chart of the observed runtime on Chrome 53 for a 2011 Macbook Pro 2GHz Intel Core i7:

![screen shot 2016-10-13 at 2 14 41 pm](https://cloud.githubusercontent.com/assets/875591/19367754/5159b53e-9151-11e6-9fee-52ce88cdf696.png)

>Fun fact: In May 2016, Haizhou Wang and Mingzhou Song implemented a new core Ckmeans algorithm (3.4.6) that improved runtime from `O(kn^2)` to `O(kn log(n))`, leading to a roughly [10x performance boost](https://cloud.githubusercontent.com/assets/875591/19367940/67688548-9152-11e6-9c2e-01e3e800bb65.png). d3-scale-cluster is one of the first javascript projects to utilize and benefit from this new algorithm.  

###Contributing

```
npm install
npm run test  # run tests
npm run build # build distributable file
```
