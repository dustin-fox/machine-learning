#include "perceptron.h"
#include <iostream>

using namespace std;

Perceptron::Perceptron(int features, int neurons) {
    numFeatures = features;
    numNeurons = neurons;
    weights = new Matrix(numFeatures + 1, numNeurons, "weightVector");
    weights->constant(0.0);
    initRand();
    weights->rand(-RANDOM_RANGE, RANDOM_RANGE);
    weights->print();
}

// Threashold function
static double threshold(double x) {
    if (x > 0)
        return 1.0;
    else
        return 0.0;
}

void Perceptron::train(Matrix *inputs, Matrix *expected, double learningRate, int trainingIterations) {
    // validate that the inputs is the right size according to numFeatures and numNeurons
    // scale data to be between 0 and 1
    Matrix *inputsNorm = new Matrix(inputs);
    inputsNorm->normalizeCols();
    // calculate activations
    for (int i = 0; i < trainingIterations; i++) {
        Matrix *activations = new Matrix(inputsNorm->dot(weights));
        // apply the threshold function to the activations
        activations->map(threshold);
        // alter weights
        weights->sub((Matrix(inputsNorm->Tdot(activations->sub(expected)))).scalarMult(learningRate));
    }
}

void Perceptron::recall(Matrix *inputs) {
    Matrix *inputsNorm = new Matrix(inputs);
    inputsNorm->normalizeCols();
    Matrix *activations = new Matrix(inputsNorm->dot(weights));
    activations->map(threshold);
    print(inputs, activations);
}

void Perceptron::print(Matrix *inputs, Matrix *outputs) {
    int inputCols = inputs->numCols() - 1;
    int outputCols = outputs->numCols();
    int totalCols = inputCols + outputCols;
    weights->print();
    for (int r = 0; r < inputs->numRows(); r++) {
        for (int c = 0; c < totalCols; c++) {
            if (c < inputCols) {
                printf("%.2f ", inputs->get(r, c));
            } else {
                printf("%.2f ", outputs->get(r, c - inputCols));
            }
        }
        printf("\n");
    }
}