#include "perceptron.h"
#include <iostream>
#include <math.h>

using namespace std;

/**
 * @brief      Sigmoid function
 */
static double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-4.0 * x));
}

// Threashold function
static double threshold(double x) {
    if (x > 0.5)
        return 1.0;
    else
        return 0.0;
}

/**
 * @brief      Constructs a Perceptron
 *
 * @param[in]  features  The number of inputs to the perceptron
 * @param[in]  neurons   The number of outputs
 */
Perceptron::Perceptron(int numFeatures, int numNeurons) {
    weights = new Matrix(numFeatures + 1, numNeurons, "weightVector");
    // initialize the weight matrix
    weights->constant(0.0);
    initRand();
    weights->rand(-RANDOM_RANGE, RANDOM_RANGE);
}

Matrix Perceptron::get_weights() {
    return *weights;
}

/**
 * @brief      Calculate the activations of the perceptron
 *
 * @param      inputs  The inputs matrix
 *
 * @return     activations  The activations matrix
 */
Matrix Perceptron::output_activation(Matrix inputs) {
    Matrix activations = Matrix(inputs.dot(weights));
    activations.map(sigmoid);
    // add bias layer
    return activations;
}

Matrix Perceptron::output_activation_threshold(Matrix inputs) {
    return output_activation(inputs).map(threshold);
}

/**
 * @brief      Caclulcate the activations of the perceptron and add a bias column
 *
 * @param      inputs  The inputs matrix
 *
 * @return     activations  The activations matrix
 */
Matrix Perceptron::hidden_activation(Matrix inputs) {
    return add_bias(output_activation(inputs));
}

Matrix Perceptron::add_bias(Matrix matrix) {
    Matrix newMatrix = Matrix(matrix.numRows(), matrix.numCols() + 1, "hidden_activation");
    newMatrix.constant(-1.0);
    for (int rows = 0; rows < matrix.numRows(); rows++) {
        for (int cols = 0; cols < matrix.numCols(); cols++) {
            newMatrix.set(rows, cols, matrix.get(rows, cols));
        }
    }
    return newMatrix;
}

Matrix Perceptron::output_error(Matrix activations, Matrix targets) {
    return (Matrix(targets).sub(activations))
           .mult(activations)
           .mult(Matrix(activations).scalarPreSub(1.0));
}

Matrix Perceptron::hidden_error(Matrix activations, Matrix prevError, Matrix prevWeights) {
    return Matrix(activations)
           .mult(Matrix(activations).scalarPreSub(1.0))
           .mult(Matrix(prevError).dotT(prevWeights));
}

void Perceptron::output_update_weights(Matrix outputError, Matrix hiddenActivation, float learningRate) {
    weights->add((hiddenActivation.Tdot(outputError))
        .scalarMult(learningRate));
}

void Perceptron::hidden_update_weights(Matrix hiddenError, Matrix inputs, float learningRate) {
    int cols = hiddenError.maxCols();
    hiddenError.narrow(cols - 1);
    weights->add((inputs.Tdot(hiddenError)).scalarMult(learningRate));
}

void Perceptron::print(Matrix inputs, Matrix outputs) {
    int inputCols = inputs.numCols() - 1;
    int outputCols = outputs.numCols();
    int totalCols = inputCols + outputCols;
    weights->print();
    for (int r = 0; r < inputs.numRows(); r++) {
        for (int c = 0; c < totalCols; c++) {
            if (c < inputCols) {
                printf("%.2f ", inputs.get(r, c));
            } else {
                printf("%.2f ", outputs.get(r, c - inputCols));
            }
        }
        printf("\n");
    }
}