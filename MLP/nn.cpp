#include "perceptron.h"
#include "../lib/mat.h"
#include <iostream>
#include <string>

using namespace std;

void get_training_data(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns);
void get_test_data(Matrix *&data, int rows, int columns);
void print_results(Matrix inputs, Matrix outputs);

int main(int argc, const char *argv[]) {
    Matrix *trainingData = NULL;
    Matrix *trainingAnswers = NULL;
    Matrix *testData = NULL;
    int inputNum = 0;
    int rows = 0;
    int hiddenNodes = 0;
    int columns = 0;
    cin >> inputNum >> hiddenNodes >> rows >> columns;
    // Create Perceptrons
    Perceptron hiddenLayer(inputNum, hiddenNodes);
    Perceptron outputLayer(hiddenNodes, columns - inputNum);
    get_training_data(trainingData, trainingAnswers, inputNum, rows, columns);
    // Train
    int trainingIterations = 10000;
    float learningRate = 0.1;
    Matrix hiddenActivation;
    Matrix outputActivation;
    Matrix hiddenError;
    Matrix outputError;
    for (int i = 0; i < trainingIterations; i++) {
        hiddenActivation = hiddenLayer.hidden_activation(trainingData);
        outputActivation = outputLayer.output_activation(hiddenActivation);
        outputError = outputLayer.output_error(outputActivation, trainingAnswers);
        hiddenError = hiddenLayer.hidden_error(hiddenActivation, outputError, outputLayer.get_weights());
        hiddenLayer.hidden_update_weights(hiddenError, trainingData, learningRate);
        outputLayer.output_update_weights(outputError, hiddenActivation, learningRate);
    }
    // Recall
    cin >> rows >> columns;
    get_test_data(testData, rows, columns);
    hiddenActivation = hiddenLayer.hidden_activation(testData);
    outputActivation = outputLayer.output_activation_threshold(hiddenActivation);
    print_results(testData, outputActivation);
}

void get_training_data(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns) {
    data = new Matrix(rows, inputNum + 1, "inputData"); // +1 for bias column
    answers = new Matrix(rows, columns - inputNum, "expectedResults");
    data->constant(-1.0);
    answers->constant(0.0);
    double temp = 0.0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (c >= inputNum) {
                cin >> temp;
                answers->set(r, c - inputNum, temp);
            } else {
                cin >> temp;
                data->set(r, c, temp);
            }
        }
    }
}

void get_test_data(Matrix *&data, int rows, int columns) {
    data = new Matrix(rows, columns + 1, "inputData"); // +1 for bias column
    data->constant(-1.0);
    double temp = 0.0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            cin >> temp;
            data->set(r, c, temp);
        }
    }
}

void print_results(Matrix inputs, Matrix outputs) {
    int inputCols = inputs.numCols() - 1;
    int outputCols = outputs.numCols();
    int totalCols = inputCols + outputCols;
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