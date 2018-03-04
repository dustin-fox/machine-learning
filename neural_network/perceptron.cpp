#include "perceptron.h"

Perceptron::Perceptron(int m, int n) {
    numFeatures = m;
    numNeurons = n;
    weights = new Matrix(numFeatures + 1, numNeurons, "weightVector");
    weights.randCol(0, -RANDOM_RANGE, RANDOM_RANGE);

}

void Perceptron::train(Matrix *inputs, Matrix *expected) {
    // validate that the inputs is the right size according to numFeatures and numNeurons
    // scale data to be between 0 and 1
    inputs->normalizeCols();

}
