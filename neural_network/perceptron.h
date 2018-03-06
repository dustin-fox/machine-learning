/**
 * Neural Network Perceptron.
 *
 * @Author Dustin Fox
 * @Version 0.1 03/01/18
 */

#include "lib/mat.h"

#define RANDOM_RANGE 1

class Perceptron {
  public:
    Perceptron(int n, int m);
    void train(Matrix *inputs, Matrix *expected, float learningRate, int trainingIterations);
    void recall(Matrix *inputs);

  private:
    int numFeatures;
    int numNeurons;
    Matrix *weights;
};