#include <stdlib.h>
#include <math.h>


// nClusters columns nValues rows
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
size_t max_t (size_t a, size_t b) {
    if (a > b) {
        return a;
    }
    return b;
}
// TODO
double ssq(size_t j, size_t i, double sumX, double sumXsq) {
    double coeff = (double) (i - j + 1);
    double muji = (sumX[i] - sumX[j - 1]) / coeff;
    double sji = sumXsq[i] - sumXsq[j - 1] - coeff * muji * muji;
    return s0i < 0 ? 0 : s0i;
}

double ssq0(size_t i, double sumX[], double sumXsq[]) {
    double s0i = sumXsq[i] - sumX[i]*sumX[i] / (double)(i + 1);
    return s0i < 0 ? 0 : s0i;
}

void fillMatrixColumn(size_t imin, size_t imax, size_t column, size_t nColumns, size_t nRows, double matrix[], size_t backtrackMatrix[], double sumX[], double sumXsq) {
    if (imin > imax) {
        return;
    }
    size_t i = imin + (imax - imin) / 2;

    matrix[column * nRows + i] = matrix[(column - 1) * nRows + i - 1];
    backtrackMatrix[column * nRows + i] = i;

    size_t jlow = column;
    if (imin > column) {
        jlow = max_t(jlow, backtrackMatrix[column * nRows + imin - 1]);
    }
    jlow = max_t(jlow, backtrackMatrix[(column -1)* nRows + i]);

    size_t jhigh = i - 1;
    if (imax < nColumns - 1) {
        jhigh = min_t(jhigh, backtrackMatrix[column * nRows + imax + 1]);
    }

    double sji;
    double sjlowi;
    double ssqjlow;
    double ssqj;

    for (size_t j = jlow; j < jhigh; j++) {
        // TODO ssq
        sji = ssq(j, i, sumX, sumXsq);
        if (sji + matrix[(column - 1)* nRows + jlow - 1] >= matrix[column * nRows + i]]) {
            break;
        }

        sjlowi = ssq(jlow, i, sumX, sumXsq);

        ssqjlow = sjlowi + matrix[(column - 1) * nRows + jlow - 1];

        if (ssqjlow < matrix[column * nRows + i]) {
            // shrink lower bound
            matrix[column * nRows + i] = ssqjlow;
            backtrackMatrix[column * nRows + i] = j;
        }
    }
    fillMatrixColumn(imin, i -1, column, nColumns, nRows, matrix, backtrackMatrix, sumX, sumXsq);
    fillMatrixColumn(i + 1, imax, column, nColumns, nRows, matrix, backtrackMatrix, sumX, sumXsq)
}

void fillMatrices (double data[], size_t nValues, double matrix[], size_t backtrackMatrix [], size_t nColumns) {
    size_t nRows = nValues;
    double sumX[nValues];
    double sumXsq[nValues];
    // we shift wrt to the median for numerical stability.
    double shift = data[nValues / 2];

    if (nValues == 0) {
        // TODO something
        return;
    }
    // TODO check overflows maybe with first and last element of array?
    sumX[0] = data[0] - shift;
    sumXsq[0] = (data[0] - shift) * (data[0] - shift);

    // First row
    for (size_t i = 1; i < nValues; i++) {
        sumX[i] = sumX[i - 1] + data[i] - shift;
        sumXsq[i] = sumXsq[i - 1] + (data[i] - shift) * (data[i] - shift);
        matrix[0 * nRows + i] = ssq0(i, sumX, sumXsq);
    }

    for (size_t k = 1; k < nColumns - 1; k++) {
       fillMatrixColumn(k, nValues - 1, k, nColumns, nRows, matrix, backtrackMatrix, sumX, sumXsq);
    }
    fillMatrixColumn(nValues - 1, nValues - 1, nColumns - 1, nColumns, nRows, matrix, backtrackMatrix, sumX, sumXsq);




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
    double * matrix = malloc(sizeMatrix* sizeof(double));
    size_t * backtrackMatrix = malloc(sizeMatrix * sizeof(size_t));

    // TODO free matrix free backtrack



}

