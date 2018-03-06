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
    // ~Perceptron();
    void train(Matrix *inputs, Matrix *expected);

  private:
    int numFeatures;
    int numNeurons;
    Matrix *weights;

  private:
    void scale(Matrix *inputs);
    void activation();
    void bias();
};