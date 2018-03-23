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
            newMatrix.set(rows, cols + 1, matrix.get(rows, cols));
        }
    }
    return newMatrix;
}

// Matrix Perceptron::output_error(Matrix activations, Matrix targets){
//     Matrix oneMatrix = new Matrix(activations.rows(), activations.cols());
//     oneMatrix.constant(1.0);
    // Matrix * error = new Matrix(targets.sub(activations).mult(activations).mult(oneMatrix.sub(activations)));
// }

// Matrix *Perceptron::hidden_error(Matrix *error){

// }

// Matrix *Perceptron::output_update_weights(Matrix *error){

// }

// Matrix *Perceptron::hidden_update_weights(Matrix *error){

// }


// void Perceptron::train(Matrix *inputs, Matrix *expected, double learningRate, int trainingIterations) {
//     // validate that the inputs is the right size according to numFeatures and numNeurons
//     // scale data to be between 0 and 1
//     Matrix *inputsNorm = new Matrix(inputs);
//     inputsNorm.normalizeCols();
//     // calculate activations
//     for (int i = 0; i < trainingIterations; i++) {
//         Matrix *activations = new Matrix(inputsNorm.dot(weights));
//         // apply the threshold function to the activations
//         activations.map(threshold);
//         // alter weights
//         weights->sub((Matrix(inputsNorm.Tdot(activations.sub(expected)))).scalarMult(learningRate));
//     }
// }

// void Perceptron::recall(Matrix *inputs) {
//     Matrix *inputsNorm = new Matrix(inputs);
//     inputsNorm.normalizeCols();
//     Matrix *activations = new Matrix(inputsNorm.dot(weights));
//     activations.map(threshold);
//     print(inputs, activations);
// }

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