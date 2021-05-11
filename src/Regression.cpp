#include "Regression.hpp"
#include "Dataset.hpp"

Regression::Regression(Dataset* dataset, int col_regr) {
    m_dataset = dataset;
    m_col_regr = col_regr;

    int d = dataset->GetDim();
    int n = dataset->GetNbrSamples();
    int x_d = d - col_regr;
    int y_d = d - x_d;

    Eigen::MatrixXd X = Eigen::MatrixXd(n, x_d + 1);
    Eigen::MatrixXd Y = Eigen::MatrixXd(n, y_d);

    for(int i = 0; i < n; ++i) {
			const std::vector<double> line = dataset->GetInstance(i);
			X(i, 0) = 1;
			for(int j = 0; j < d; ++j) {
				if(j >= m_col_regr){
					Y(i,j - x_d) = line[j];
				}
                else{
				    X(i, j + 1) = line[j];
                }
			}
	}
    m_X = new Eigen::MatrixXd(X);
    m_Y = new Eigen::MatrixXd(Y);
}

Regression::~Regression(){
    m_X->resize(0, 0);
	m_Y->resize(0, 0);
	delete m_X;
	delete m_Y;
}

int Regression::GetColRegr() const {
    return m_col_regr;
}

Dataset* Regression::GetDataset() const {
    return m_dataset;
}

Eigen::MatrixXd* Regression::GetInput(){
    return m_X;
}

Eigen::MatrixXd* Regression::GetOutput(){
    return m_Y;
}