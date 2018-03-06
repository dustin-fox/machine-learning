#include "perceptron.h"

Perceptron::Perceptron(int features, int neurons) {
    numFeatures = features;
    numNeurons = neurons;
    weights = new Matrix(numFeatures + 1, numNeurons, "weightVector");
    weights->constant(0.0);
    initRand();
    weights->rand(-1.0, 1.0);
}

// Threashold function
static double threshold(double x) {
    if (x > 0)
        return 1.0;
    else
        return 0.0;
}

void Perceptron::train(Matrix *inputs, Matrix *expected) {
    // validate that the inputs is the right size according to numFeatures and numNeurons
    // scale data to be between 0 and 1
    inputs->normalizeCols();
    inputs->print();
    weights->print();
    // calculate activations
    Matrix *activations = new Matrix(inputs->dot(weights));
    activations->print();
    // apply the threshold function to the activations
    activations->map(threshold);
    activations->print();

}