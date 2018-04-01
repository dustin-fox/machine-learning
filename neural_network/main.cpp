#include "perceptron.h"
#include "../lib/mat.h"
#include <iostream>
#include <string>

using namespace std;

void getTrainingData(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns);
void getTestData(Matrix *&data, int rows, int columns);

int main(int argc, const char *argv[]) {
    Matrix *trainingData = NULL;
    Matrix *trainingAnswers = NULL;
    Matrix *testData = NULL;
    int inputNum = 0;
    int rows = 0;
    int columns = 0;
    cin >> inputNum >> rows >> columns;
    // Create Perceptron
    Perceptron perceptron(inputNum, columns - inputNum);
    getTrainingData(trainingData, trainingAnswers, inputNum, rows, columns);
    // Train
    perceptron.train(trainingData, trainingAnswers, 0.1, 1000);
    // Recall
    cin >> rows >> columns;
    getTestData(testData, rows, columns);
    perceptron.recall(testData);
}

void getTrainingData(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns) {
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

void getTestData(Matrix *&data, int rows, int columns) {
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