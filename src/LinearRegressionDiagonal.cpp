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

	MatrixXd beta = MatrixXd::Zero(m_X->cols(), m_Y->cols());
	MatrixXd X_t = m_X->transpose();
	
	for(int i = 0; i < m_Y->cols(); i++){
		MatrixXd X_tmp(n, 2);
		
		
		for(unsigned j = 0; j < n; ++j) {
			X_tmp(j,0) = (*m_X)(j,0);
			X_tmp(j,1) = (*m_X)(j,i+1);
		}
		MatrixXd X_t_tmp = X_tmp.transpose();
		MatrixXd A = X_t_tmp * X_tmp;
		MatrixXd B = X_t_tmp * (*m_Y).col(i);
		MatrixXd tmp = A.colPivHouseholderQr().solve(B);
		beta(0,i) = tmp(0,0);
		beta(i+1,i) = tmp(1,0);
	}

	m_beta = new MatrixXd(beta);
}
