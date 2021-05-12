#include <Eigen/Dense>
#include <Eigen/Core>
#include "Dataset.hpp"
#include "LinearRegression.hpp"
#include <math.h> 

#ifndef LINEARREGRESSIONDIAGONAL_HPP
#define LINEARREGRESSIONDIAGONAL_HPP
/**
  The LinearRegressionDiagonal class inherits from the Regression class, stores the coefficient and provides a bunch of specific methods.
*/
class LinearRegressionDiagonal : public LinearRegression {
  
public:

  /**
      The linear regression method fits a linear regression coefficient to col_regr using the provided Dataset. It calls setCoefficients under the hood.
     @param dataset a pointer to a dataset
     @param m_col_regr the integer of the column index of Y
    */
	LinearRegressionDiagonal(Dataset* dataset, int col_regr);

	void SetCoefficients();
};

#endif //LINEARREGRESSIONDiagonal_HPP
