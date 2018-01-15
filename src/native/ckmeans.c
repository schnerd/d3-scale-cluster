#include <stdlib.h>
#include <math.h>

int compare_doubles(const void *p, const void *q) {
    double x = *(const double *)p;
    double y = *(const double *)q;
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    }
    return 0;
}

size_t unique_sort_count (double array[], size_t len) {
    if (len == 0) {
        return 0;
    }
    size_t uniqueValueCount = 1;
    double lastSeenValue = array[0];
    for (size_t i = 1; i < len; i++) {
        if (array[i] != lastSeenValue) {
            uniqueValueCount++;
            lastSeenValue = array[i];
        }
    }
    return uniqueValueCount;
}
size_t min_t (size_t a, size_t b) {
    if (a < b) {
        return a;
    }
    return b;
}
void ckmeans (double data[],size_t nValues, double output[], size_t *nClustersFinal, size_t nClusters) {
    qsort(data, nValues, sizeof *data, &compare_doubles);
    // we'll use as a maximum number of clusters
    int uniqueCount = unique_sort_count(data, nValues);
    if (uniqueCount == 1) {
        *nClustersFinal = 1;
        output[0] = data[0];
        return;
    }
    nClusters = min_t(nClusters, uniqueCount);
    // *nClustersFinal = nClusters;
    const size_t sizeMatrix = nClusters * nValues;
    double matrix[sizeMatrix];
    double backtrackMatrix[sizeMatrix];



}

