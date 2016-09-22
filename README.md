# d3-scale-cluster

D3 scale that clusters data into discrete groups. Similar to [quantile scales](https://github.com/d3/d3-scale/blob/master/README.md#scaleQuantile), the cluster scale maps a sampled input domain to a discrete range. The number of values in the output range determines the number of clusters that will be computed from the domain. The graphic below demonstrates how cluster compares to d3's quantile and quantize scales:

<img width="420" alt="d3 scale cluster example" src="https://cloud.githubusercontent.com/assets/875591/18608070/0213d7ce-7cdf-11e6-89aa-1b0e18e63cc8.png">

Clusters are computed using a 1-dimensional clustering algorithm explained later in this document. While this algorithm does produce nice results, it should be noted that it can be an order of magnitude slower than quantile and quantize. You should do your own testing to ensure it meets the performance requirements of your application.

To use this scale, you may install via npm:
```
npm install d3-cluster-scale
```

Or include a `<script>` tag on your page after d3
```
<script src="https://unpkg.com/d3-scale-cluster@1.0.1/dist/d3-scale-cluster.min.js"></script>
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

For clustering, this project uses the [Ckmeans](http://simplestatistics.org/docs/#ckmeans) algorithm implementation from the [simple-statistics](https://github.com/simple-statistics/simple-statistics) library (the original algorithm was written by [Haizhou Wang and Mingzhou Song](http://journal.r-project.org/archive/2011-2/RJournal_2011-2_Wang+Song.pdf)). This algorithm is a minor improvement on the [Jenks Natural Breaks](https://en.wikipedia.org/wiki/Jenks_natural_breaks_optimization) algorithm developed by cartographer George Jenks. Tom MacWright wrote previously about [using Jenks Natural Breaks for d3 choropleths](http://www.macwright.org/2013/02/18/literate-jenks.html), but to my knowledge it was never turned into a reusable d3 scale.

As noted previously in this document, the Ckmeans algorithm is much slower than other d3 scales like quantile and quantize–with an algorithmic time complexity of O(k*n^2), where `k` is the number of clusters. For a sample size of 1000, the algorithm takes roughly 30ms on Chrome 53 for a 2013 Macbook Pro 3.1GHz Intel Core i7. A sample size of 3,500 (roughly the number of counties in a US county choropleth) takes roughly 270ms on the same machine. Consider these performance limitations when you are deciding whether this is the right solution for your application. I'll be investigating faster clustering algorithms to use in this scale in the future, and would love to hear any suggestions if you have them.

###Contributing

```
npm install
npm run test  # run tests
npm run build # build distributable file
```
