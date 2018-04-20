#include "lib/mat.h"
#include <iostream>
#include <limits>
#include <cmath>

typedef char **cstring;

void getData(Matrix &trainingData, Matrix &testData, cstring &labels);
void buildKDTree(const Matrix &data, Matrix &tree);
bool buildKDTreeAux(Matrix &data, int currCol, int rowStart, int rowEnd);
double dist2(const Matrix &tree, const Matrix &node, const int &row);
void nearest(const Matrix &tree, const Matrix &node);
bool nearestAux(const Matrix &tree, const Matrix &node, int startRow, int endRow, double &nearestDistance, int &nearestRow);

int main() {
    cstring labels;
    Matrix trainingData;
    Matrix testData;
    Matrix KDTree;
    getData(trainingData, testData, labels);
    buildKDTree(trainingData, KDTree);
    KDTree.printLabeledRow(labels, "KDTree version of matrix");
}

void getData(Matrix &trainingData, Matrix &testData, cstring &labels) {
    // Read Data in from standard input
    labels = trainingData.readLabeledRow();
    testData.read();
}

void buildKDTree(const Matrix &data, Matrix &tree) {
    tree = Matrix(data);
    if (!buildKDTreeAux(tree, 1, 0, tree.numRows() - 1)) {
        std::cerr << "ERROR while building kd tree.." << std::endl;
        tree.setName("broken kd tree");
    } else {
        tree.setName("kd tree");
    }
}

bool buildKDTreeAux(Matrix &tree, int currCol, int startRow, int endRow) {
    // Feature wrap around
    if (currCol == tree.numCols()) {
        currCol = 1;
    }
    // Sort by currCol
    tree.sortRowsByCol(currCol, startRow, endRow);
    // Recurse on remaining tree
    int length = endRow - startRow;
    if (length <= 1) {
        return true;
    } else {
        int medianRow = startRow + length / 2;
        if (buildKDTreeAux(tree , currCol + 1, startRow, medianRow - 1)) {
            return buildKDTreeAux(tree, currCol + 1, medianRow + 1, endRow);
        } else {
            return false;
        }
    }
    // Should never actually reach this point, but just to be sure.
    return false;
}

double dist2(const Matrix &tree, const Matrix &node, const int &row) {
    double sum = 0.0;
    for (int i = 1; i < tree.numCols(); i++) {
        sum += pow((tree.get(row, i) - node.get(0, i)), 2.0);
    }
    return sqrt(sum);
}

void nearest(const Matrix &tree, const Matrix &node) {
    double nearestDistance = std::numeric_limits<double>::max();
    int nearestRow = 0;
    nearestAux(tree, node, 0, tree.numRows(), nearestDistance, nearestRow);
}

bool nearestAux(const Matrix &tree, const Matrix &node, int startRow, int endRow, double &nearestDistance, int &nearestRow) {
    int length = endRow - startRow;
    int medianRow = startRow + length / 2;
    if (length <= 1) {

    }
}
