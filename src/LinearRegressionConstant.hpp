#include <Eigen/Dense>
#include <Eigen/Core>
#include "Dataset.hpp"
#include "Regression.hpp"
#include <math.h> 

#ifndef LINEARREGRESSIONCONSTANT_HPP
#define LINEARREGRESSIONCONSTANT_HPP

/**
  The LinearRegressionConstant class inherits from the Regression class, stores the coefficient and provides a bunch of specific methods.
*/
class LinearRegressionConstant : public Regression {
protected:
    /**
      The linear regression constant coefficient.
    */
	double m_beta;
  
public:
    /**
      The linear regression method fits a linear regression coefficient to (col_regr, end) using the provided Dataset. It calls setCoefficients under the hood.
     @param dataset a pointer to a dataset
     @param m_col_regr the integer of the column index of Y
    */
	LinearRegressionConstant(Dataset* dataset, int col_regr);
    /**
      The destructor (frees m_beta).
    */
  ~LinearRegressionConstant();
    /**
      The setter method of the private attribute m_beta which is called by LinearRegressionConstant.
    */
	void SetCoefficients();
  /**
      The getter method of the private attribute m_beta.
    */
	const double GetCoefficients() const;
    /**
      Prints the contents of the private attribute m_beta.
    */
	void ShowCoefficients() const;
    /**
      The SumsOfSquares method calculates the ESS, RSS and TSS that will be initialized, passed by reference and thereafter printed by test_linear.
    */
	void SumsOfSquares( Dataset* dataset, double& ess, double& rss, double& tss ) const;
    /**
      The estimate method outputs the predicted Y for a given point x.
     @param x the point for which to estimate Y.
    */
	Eigen::VectorXd Estimate( const Eigen::VectorXd & x ) const;
};

#endif //LinearRegressionConstant_HPP