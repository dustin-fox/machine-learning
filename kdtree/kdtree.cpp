#include "lib/mat.h"
#include <iostream>

typedef char **cstring;

void getData(Matrix &trainingData, Matrix &testData, cstring &labels);
void buildKDTree(const Matrix &data, Matrix &tree);
bool buildKDTree_R(Matrix &data, int currCol, int rowStart, int rowEnd);

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
    if (!buildKDTree_R(tree, 1, 0, tree.numRows() - 1)) {
        std::cerr << "ERROR while building kd tree.." << std::endl;
        tree.setName("broken kd tree");
    } else {
        tree.setName("kd tree");
    }
}

bool buildKDTree_R(Matrix &data, int currCol, int startRow, int endRow) {
    // Feature wrap around
    if (currCol == data.numCols()) {
        currCol = 1;
    }
    // Sort by currCol
    data.sortRowsByCol(currCol, startRow, endRow);
    // Recurse on remaining data
    int length = endRow - startRow;
    if (length <= 1) {
        return true;
    } else {
        int medianRow = startRow + length / 2;
        if (buildKDTree_R(data , currCol + 1, startRow, medianRow - 1)) {
            return buildKDTree_R(data, currCol + 1, medianRow + 1, endRow);
        } else {
            return false;
        }
    }
    // Should never actually reach this point, but just to be sure.
    return false;
}
