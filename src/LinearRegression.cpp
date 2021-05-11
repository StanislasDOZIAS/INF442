#include "LinearRegression.hpp"
#include "Dataset.hpp"
#include "Regression.hpp"
#include<iostream>
#include<cassert>


using namespace Eigen;

LinearRegression::LinearRegression( Dataset* dataset, int col_regr ) 
: Regression(dataset, col_regr) {
	SetCoefficients();
}

LinearRegression::~LinearRegression() {
	m_beta->resize(0, 0);
	delete m_beta;
}

void LinearRegression::SetCoefficients() {
	int n = m_dataset->GetNbrSamples();
	int d = m_dataset->GetDim();
	MatrixXd X_t = m_X->transpose();

	MatrixXd A = X_t * (*m_X);

	MatrixXd B = X_t * (*m_Y);

	MatrixXd beta = A.colPivHouseholderQr().solve(B);

	m_beta = new MatrixXd(beta);
}

const Eigen::MatrixXd* LinearRegression::GetCoefficients() const {
	if (!m_beta) {
		std::cout<<"Coefficients have not been allocated."<<std::endl;
		return NULL;
	}
	return m_beta;
}

void LinearRegression::ShowCoefficients() const {
	if (!m_beta) {
		std::cout<<"Coefficients have not been allocated."<<std::endl;
		return;
	}
	
	std::cout<< "beta = (";
	for (int i=0; i<m_beta->size(); i++) {
		std::cout<< " " << (*m_beta)(i);
	}
	std::cout << " )"<<std::endl;
}

void LinearRegression::SumsOfSquares( Dataset* dataset, double& ess, double& rss, double& tss ) const {
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

Eigen::VectorXd LinearRegression::Estimate( const Eigen::VectorXd & x ) const {
	VectorXd v = (*m_beta).transpose() * x;
	return v;
}
