#include "perceptron.h"
#include <iostream>

using namespace std;

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

void Perceptron::train(Matrix *inputs, Matrix *expected, float learningRate, int trainingIterations) {
    // validate that the inputs is the right size according to numFeatures and numNeurons
    // scale data to be between 0 and 1
    inputs->normalizeCols();
    // calculate activations
    for (int i = 0; i < trainingIterations; i++) {
        Matrix *activations = new Matrix(inputs->dot(weights));
        // apply the threshold function to the activations
        activations->map(threshold);
        // alter weights
        weights->sub((Matrix(inputs->Tdot(activations->sub(expected)))).scalarMult(learningRate));
    }
}

void Perceptron::recall(Matrix *inputs) {
    Matrix *activations = new Matrix(inputs->dot(weights));
    activations->map(threshold);
    cout << "The Answers:\n";
    inputs->print();
    activations->print();
}