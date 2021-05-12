#include "LinearRegressionConstant.hpp"
#include "Dataset.hpp"
#include "Regression.hpp"
#include<iostream>
#include<cassert>


using namespace Eigen;

LinearRegressionConstant::LinearRegressionConstant( Dataset* dataset, int col_regr ) 
: Regression(dataset, col_regr) {
	SetCoefficients();
}

LinearRegressionConstant::~LinearRegressionConstant() {}

void LinearRegressionConstant::SetCoefficients() {
	int n = m_dataset->GetNbrSamples();
	int d = m_dataset->GetDim();
    MatrixXd X = m_X->rightCols(m_X->cols() - 1);
	MatrixXd X_t = X.transpose();

	MatrixXd A = X_t * X;

	MatrixXd B = X_t * (*m_Y);

	MatrixXd beta(A.rows(), A.cols());

    
    for(unsigned i = 0; i < A.rows(); ++i) {
        
        for(unsigned j = 0; j < A.cols(); ++j) {
            beta(i,j) = (A(i,j) != 0) ? B(i,j) / A(i,j) : 0;
        }
        
    }
    


	m_beta = beta.mean();
}

const double LinearRegressionConstant::GetCoefficients() const {
	if (!m_beta) {
		std::cout<<"Coefficients have not been allocated."<<std::endl;
		return NULL;
	}
	return m_beta;
}

void LinearRegressionConstant::ShowCoefficients() const {
	std::cout<< "beta = (";
	std::cout<< " " << m_beta;
	std::cout << " )"<<std::endl;
}

void LinearRegressionConstant::SumsOfSquares( Dataset* dataset, double& ess, double& rss, double& tss ) const {
	assert(dataset->GetDim()==m_dataset->GetDim());
	int n = dataset->GetNbrSamples();
	int d = m_dataset->GetDim();
	MatrixXd Y_prime = MatrixXd::Zero(n, m_Y->cols());

	for(int i = 0; i < n; ++i) {
			Eigen::VectorXd x = m_X->row(i);
			VectorXd tmp = Estimate(x);
			for(int j = 0;j < m_Y->cols();j++)
			{
				Y_prime(i,j) = tmp[j];
			}
	}
	VectorXd y_bar = (*m_Y).colwise().sum() / ((double) n);

	ess = 0;
	rss = 0;
	tss = 0;

	for(int i = 0; i < n; ++i) {
		VectorXd y_p = Y_prime.row(i);
		VectorXd y = m_Y->row(i);
		ess += (y_p - y_bar).squaredNorm();
		rss += (y_p - y).squaredNorm();
		tss += (y - y_bar).squaredNorm();
	}
}

Eigen::VectorXd LinearRegressionConstant::Estimate( const Eigen::VectorXd & x ) const {
    VectorXd xx = x.tail(x.size() - 1);
	VectorXd v = x * m_beta;
	return v;
}
