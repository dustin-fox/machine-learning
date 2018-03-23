/**
 * Neural Network Perceptron.
 *
 * @Author Dustin Fox
 * @Version 0.1 03/01/18
 */

#include "lib/mat.h"

#define RANDOM_RANGE 0.05

class Perceptron {
  public:
    Perceptron(int n, int m);
    Matrix output_activation(Matrix inputs);
    Matrix hidden_activation(Matrix inputs);
    Matrix add_bias(Matrix matrix);
    // void train(Matrix *inputs, Matrix *expected, double learningRate, int trainingIterations);
    // void recall(Matrix *inputs);

  private:
    void print(Matrix inputs, Matrix outputs);
    Matrix *weights;
};