#include "lib/mat.h"

void getData(Matrix &trainingData, Matrix &testData, char** labels);

int main() {
    char** labels;
    Matrix trainingData;
    Matrix testData;
    getData(trainingData, testData, labels);
}

void getData(Matrix &trainingData, Matrix &testData, char** labels){
    // Read Data in from standard input
    labels = trainingData.readLabeledRow();
    testData.read();
}