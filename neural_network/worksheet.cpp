#include "lib/mat.h"
#include <iostream>

using namespace std;

int main() {
    cout << "New Matrix:\n";
    Matrix mat = new Matrix(10,10, "testmatrix");
    mat = mat.randCol(1,10.00,100.00);
    mat = mat.randCol(2,10.00,100.00);
    mat = mat.randCol(3,10.00,100.00);
    mat = mat.randCol(4,10.00,100.00);
    mat = mat.randCol(5,10.00,100.00);
    mat = mat.randCol(6,10.00,100.00);
    mat = mat.randCol(7,10.00,100.00);
    mat = mat.randCol(8,10.00,100.00);
    mat.print();
}