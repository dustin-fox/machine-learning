#include "lib/mat.h"
#include <iostream>
#include <limits>
#include <cmath>

typedef char **cstring;

void getData(Matrix &trainingData, Matrix &testData, cstring &labels);
void buildKDTree(const Matrix &data, Matrix &tree);
bool buildKDTreeAux(Matrix &data, int currCol, int rowStart, int rowEnd);
double dist2(const Matrix &tree, const int &treeRow, const Matrix &node, const int &nodeRow);
void checkBest(const Matrix &tree, const int &treeRow, const Matrix &node, const int &nodeRow, double &nearestDistance, int &nearestRow);
void nearest(const Matrix &tree, const Matrix &node, cstring &labels);
bool nearestAux(const Matrix &tree,
                const Matrix &node,
                const int &nodeRow,
                int currCol,
                const int &startRow,
                const int &endRow,
                double &nearestDistance,
                int &nearestRow);

int main() {
    cstring labels;
    Matrix trainingData;
    Matrix testData;
    Matrix KDTree;
    getData(trainingData, testData, labels);
    buildKDTree(trainingData, KDTree);
    KDTree.printLabeledRow(labels, "KDTree version of matrix");
    printf("\n\n");
    nearest(KDTree, testData, labels);
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

double dist2(const Matrix &tree, const int &treeRow, const Matrix &node, const int &nodeRow) {
    double sum = 0.0;
    for (int i = 1; i < tree.numCols(); i++) {
        sum += pow((tree.get(treeRow, i) - node.get(nodeRow, i - 1)), 2.0);
    }
    return sqrt(sum);
}

void checkBest(const Matrix &tree, const int &treeRow, const Matrix &node, const int &nodeRow, double &nearestDistance, int &nearestRow) {
    double newDist = dist2(tree, treeRow, node, nodeRow);
    if (newDist < nearestDistance) {
        nearestDistance = newDist;
        nearestRow = treeRow;
        // printf("***MINDIST: %.3f MINROW: %d\n", nearestDistance, nearestRow);
    }
}

void nearest(const Matrix &tree, const Matrix &node, cstring &labels) {
    double nearestDistance;
    int currCol;
    int nearestRow;
    for (int row = 0; row < node.numRows(); row++) {
        nearestDistance = std::numeric_limits<double>::max();
        currCol = 1;
        nearestRow = 0;
        printf("SOLVE:");
        for (int feature = 0; feature < node.numCols(); feature++) {
            printf(" %.2f", node.get(row, feature));
        }
        printf("\n");
        nearestAux(tree, node, row, currCol, 0, tree.numRows() - 1, nearestDistance, nearestRow);
        //Printing
        printf("BESTLEAF: %.3f %d\n", nearestDistance, nearestRow);
        printf("Ans:");
        for (int feature = 1; feature < tree.numCols(); feature++) {
            printf(" %.2f", tree.get(nearestRow, feature));
        }
        printf(" %d %s\n\n", nearestRow, labels[(int)tree.get(nearestRow, 0)]);
    }
}

bool nearestAux(const Matrix &tree,
                const Matrix &node,
                const int &nodeRow,
                int currCol,
                const int &startRow,
                const int &endRow,
                double &nearestDistance,
                int &nearestRow) {
    printf("RANGE: %d to %d\n", startRow, endRow);
    // Feature wrap around
    if (currCol == tree.numCols()) {
        currCol = 1;
    }
    // Calculated values
    int length = endRow - startRow;
    // Traverse
    if (length <= 2) { // handle leaf
        // printf("***LEAF\n");
        checkBest(tree, startRow, node, nodeRow, nearestDistance, nearestRow);
        checkBest(tree, endRow, node, nodeRow, nearestDistance, nearestRow);
        return true;
    } else if (length > 2) { // handle non leaf
        // printf("***TREE\n");
        int parentRow = startRow + length / 2;
        // check best child
        bool checkedLower = false;
        if (node.get(nodeRow, currCol - 1) <= tree.get(parentRow, currCol)) {
            checkedLower = true;
            nearestAux(tree,
                       node,
                       nodeRow,
                       currCol + 1,
                       startRow,
                       parentRow - 1,
                       nearestDistance,
                       nearestRow);
        } else {
            checkedLower = false;
            nearestAux(tree,
                       node,
                       nodeRow,
                       currCol + 1,
                       parentRow + 1,
                       endRow,
                       nearestDistance,
                       nearestRow);
        }
        // check to see if you can shortcut or if we need to check other child
        double distFromParent = abs(node.get(nodeRow, currCol - 1) - tree.get(parentRow, currCol));
        // printf("***DISTFROMPARENT: %.3f\n", distFromParent);
        if (distFromParent < nearestDistance) {
            printf("BESTPARENT1(%d): %.3f\n", parentRow, distFromParent);
            // check parent node
            checkBest(tree, parentRow, node, nodeRow, nearestDistance, nearestRow);
            if (nearestDistance == 0) {
                // quit only if we know the children can't be better
                return true;
            }
            // check other child
            if (checkedLower) {
                nearestAux(tree,
                           node,
                           nodeRow,
                           currCol + 1,
                           parentRow + 1,
                           endRow,
                           nearestDistance,
                           nearestRow);
            } else {
                nearestAux(tree,
                           node,
                           nodeRow,
                           currCol + 1,
                           startRow,
                           parentRow - 1,
                           nearestDistance,
                           nearestRow);
            }
        } else {
            return true;
        }
    }
    return false;
}
