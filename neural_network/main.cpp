#include "perceptron.h"
#include "lib/mat.h"
#include <iostream>
#include <string>

using namespace std;

void getData(Matrix *&data, Matrix *&answers);

int main(int argc, const char *argv[]) {
    Matrix *data = NULL;
    Matrix *answers = NULL;
    getData(data, answers);
    data->print();
    answers->print();
}

void getData(Matrix *&data, Matrix *&answers) {
    int inputNum = 0;
    int rows = 0;
    int columns = 0;
    cin >> inputNum >> rows >> columns;
    data = new Matrix(rows, inputNum, "inputData");
    answers = new Matrix(rows, columns - inputNum, "expectedResults");
    data->constant(0);
    answers->constant(0);
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