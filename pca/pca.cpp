/**
 * Principle Component Analysis
 * Implemented in c++
 * @author Dustin Fox
 * @date 04/01/18
 *
 * def pca(data,nRedDim=0,normalise=1):
 *    # Centre data
 *    m = np.mean(data,axis=0)
 *    data -= m
 *
 *    # Covariance matrix
 *    C = np.cov(np.transpose(data))
 *
 *    # Compute eigenvalues and sort into descending order
 *    evals,evecs = np.linalg.eig(C)
 *    indices = np.argsort(evals)
 *    indices = indices[::-1]
 *    evecs = evecs[:,indices]
 *    evals = evals[indices]
 *    if nRedDim>0:
 *       evecs = evecs[:,:nRedDim]
 *    if normalise:
 *       for i in range(np.shape(evecs)[1]):
 *          evecs[:,i] / np.linalg.norm(evecs[:,i]) * np.sqrt(evals[i])
 *
 *    # Produce the new data matrix
 *    x = np.dot(np.transpose(evecs),np.transpose(data))
 *
 *    # Compute the original data again
 *    y=np.transpose(np.dot(evecs,x))+m
 *    return x,y,evals,evecs
 */
#include "../lib/mat.h"

void pca(Matrix data) {

}

void read_test_data() {
    
}

int main() {

}