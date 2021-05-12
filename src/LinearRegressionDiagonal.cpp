#include "LinearRegressionDiagonal.hpp"
#include "Dataset.hpp"
#include "Regression.hpp"
#include<iostream>
#include<cassert>


using namespace Eigen;

LinearRegressionDiagonal::LinearRegressionDiagonal( Dataset* dataset, int col_regr ) 
: LinearRegression(dataset, col_regr) {
	SetCoefficients();
}

void LinearRegressionDiagonal::SetCoefficients() {
	int n = m_dataset->GetNbrSamples();
	int d = m_dataset->GetDim();
	MatrixXd X_t = m_X->transpose();

	MatrixXd A = X_t * (*m_X);

	MatrixXd B = X_t * (*m_Y);

	for(unsigned i = 0; i < A.rows(); ++i) {
		for(unsigned j = 0; j < B.cols(); ++j) {
			if(i != j && i != 0){
				A(i,j) = 0;
				B(i,j) = 0;
			}
		}
	}
	

	MatrixXd beta = A.colPivHouseholderQr().solve(B);

	m_beta = new MatrixXd(beta);
}
