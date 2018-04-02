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
#include <iostream>

#include "lib/mat.h"

int main() {
    Matrix mean("Mean");
    Matrix standardDiviation("StandardDiviation");
    Matrix normalizedData("Normalized");
    Matrix covariance("Covariance");
    Matrix eigenvectors("EigenVectors");
    Matrix eigenvalues("EigenValues");
    Matrix compressedData("Encoded");
    Matrix newData("NewData");
    Matrix originalData("Pic");
    int eigenvectorCount = 0;
    double dataElementsCount = 0.f;
    // Read in the number of eigenvectors
    std::cin >> eigenvectorCount;
    // Read in picture to analyze
    originalData.readImagePpm("", "");
    originalData.writeImagePpm("z-before.ppm", "");
    dataElementsCount = originalData.numCols() * originalData.numRows();
    originalData.printSize();
    // Center the Data
    mean = originalData.meanVec();
    standardDiviation = originalData.stddevVec();
    normalizedData = originalData;
    normalizedData.subRowVector(mean);
    normalizedData.divRowVector(standardDiviation);
    // Create the covarianve matrix
    covariance = normalizedData.cov();
    // Compute the eigenvalues and sort in decending order
    eigenvectors = covariance;
    eigenvalues = eigenvectors.eigenSystem();
    eigenvalues.printSize();
    eigenvectors.shorten(eigenvectorCount);
    eigenvalues.narrow(eigenvectorCount);
    // Produce the new data matrix
    compressedData = eigenvectors.dotT(normalizedData);
    compressedData.transposeSelf().printSize();
    compressedData.transposeSelf();
    // Decompress data
    newData = ((eigenvectors.Tdot(compressedData)).transpose()).multRowVector(standardDiviation).addRowVector(mean);
    // Find the data loss from compression using sum of squares distance.
    std::printf("DIST: %.6g\n", originalData.dist2(newData) / dataElementsCount);
    // Create a new .ppm file from newData
    newData.writeImagePpm("z-after.ppm", "");
    return 0;
}