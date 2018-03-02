/**
 * Neural Network Perceptron.
 *
 * @Author Dustin Fox
 * @Version 0.1 03/01/18
 */

#include "lib/mat.h"

#define RANDOM_RANGE 100

class Perceptron {
  public:
    Perceptron(int n, int m);
    ~Perceptron();
    train(Matrix input, Matrix output);
    guess(Matrix input);

  private:
    int numInputs;
    int numOutputs;
    Matrix inputs;
    Matrix weights;

  private:
    activation();
    randomizeWeights();
}

Perceptron::Perceptron(int inum, int onum) {
    numInputs = inum;
    numOutputs = onum;
    inputs = new Matrix(numInputs, 0, "inputVector");
    weights = new Matrix(numInputs, 0, "weightVector");
    weights.randCol(0, -RANDOM_RANGE, RANDOM_RANGE);

}
