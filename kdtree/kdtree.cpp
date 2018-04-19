#include "lib/mat.h"
#include <iostream>

void getData(Matrix &trainingData, Matrix &testData, char **labels);
Matrix buildKDTree(const Matrix &data);
bool buildKDTree_(Matrix &data, int currCol, int rowStart, int rowEnd);

int main() {
    char **labels;
    Matrix trainingData;
    Matrix testData;
    Matrix KDTree;
    getData(trainingData, testData, labels);
    KDTree = buildKDTree(trainingData);
    KDTree.print();
}

void getData(Matrix &trainingData, Matrix &testData, char **labels) {
    // Read Data in from standard input
    labels = trainingData.readLabeledRow();
    testData.read();
}

Matrix buildKDTree(const Matrix &data) {
    Matrix tree = Matrix(data);
    if (!buildKDTree_(tree, 1, 0, tree.numRows() - 1)) {
        std::cout << "\nERROR!!!\n";
    }
    return tree;
}

bool buildKDTree_(Matrix &data, int currCol, int startRow, int endRow) {
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
        if (buildKDTree_(data , currCol + 1, startRow, medianRow - 1)) {
            return buildKDTree_(data, currCol + 1, medianRow + 1, endRow);
        } else {
            return false;
        }
    }
}

void printKDTree()