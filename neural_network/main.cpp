#include "perceptron.h"
#include "lib/mat.h"
#include <iostream>
#include <string>

using namespace std;

void getData(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns);

int main(int argc, const char *argv[]) {
    Matrix *data = NULL;
    Matrix *answers = NULL;
    int inputNum = 0;
    int rows = 0;
    int columns = 0;
    cin >> inputNum >> rows >> columns;
    // Create Perceptron
    Perceptron perceptron(inputNum, columns - inputNum);
    getData(data, answers, inputNum, rows, columns);
    // Debug
    data->print();
    answers->print();
    // Train
    perceptron.train(data, answers, 0.3, 100);
    perceptron.recall(data);
}

void getData(Matrix *&data, Matrix *&answers, int inputNum, int rows, int columns) {
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
                cout << "ans";
            } else {
                cin >> temp;
                data->set(r, c, temp);
                cout << "dat";
            }
            cout << "setting " << r << c << " to" << temp << endl;
        }
    }
}