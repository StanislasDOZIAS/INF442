#include <iostream>
#include <cmath>
#include <typeinfo> 
#include <time.h>

#include "./Dataset.hpp"
#include "./LinearRegression.hpp"
#include "./LinearRegressionConstant.hpp"
#include "./LinearRegression.hpp"
#include "./LinearRegressionDiagonal.hpp"

void print_vec(Eigen::VectorXd const &v){
	for(unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

template<class T>
void test_regr_linear(Dataset &train_data, Dataset &test_data, int col_regr){
	float temps;
    clock_t t1, t2;
 
    t1 = clock();
 
    T tester(&train_data, col_regr);
     
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	

	std::cout << std::endl <<
	"Régression linéaire " << typeid(T).name() << std::endl
         << std::endl;

	//tester.ShowCoefficients();
    std::cout << "Time of execution = " << temps << std::endl;

    std::cout << std::endl;
    std::cout << "Testing the Estimate method on the first sample of test_file" << std::endl;
    std::vector<double> first_sample = test_data.GetInstance(0);
    Eigen::VectorXd first_sample_eigen(col_regr + 1);
    Eigen::VectorXd first_res_eigen(col_regr);
	first_sample_eigen(0) = 1;
    for (int j = 0; j < col_regr; j++) {
        first_sample_eigen(j+1) = first_sample[j];
		first_res_eigen(j) = first_sample[j + col_regr];
    }

    std::cout << "The true value of y for the first sample of test_file is:" << std::endl;
    print_vec(first_res_eigen);
    std::cout << "The estimated value of y for the first sample of test_file is:" << std::endl;
    Eigen::VectorXd cev = tester.Estimate(first_sample_eigen);
    print_vec(cev);

    std::cout
         << std::endl;
    double ct_ess, ct_rss, ct_tss;
    tester.SumsOfSquares(&train_data, ct_ess, ct_rss, ct_tss);
    std::cout << "Sums of Squares wrt training set:" << std::endl
              << " ESS=" << ct_ess << std::endl
              << " RSS=" << ct_rss << std::endl
              << " TSS=" << ct_tss << std::endl
              << " R2=" << ct_ess / ct_tss << std::endl
              << " MSE=" << ct_rss / train_data.GetNbrSamples() << std::endl;
    double cr_ess, cr_rss, cr_tss;
    tester.SumsOfSquares(&test_data, cr_ess, cr_rss, cr_tss);
    std::cout << "Sums of Squares wrt regression set:" << std::endl
              << " ESS=" << cr_ess << std::endl
              << " RSS=" << cr_rss << std::endl
              << " TSS=" << cr_tss << std::endl
              << " MSE=" << cr_rss / test_data.GetNbrSamples() << std::endl;

}


int main(int argc, char **argv)
{
	if(argc == 2 && strcmp(argv[1] ,"help") == 0 || argc > 5 || argc < 3){
		std::cout << "./inf442 train_data.csv test_data.csv [has_header=1] [delim=',']" << std::endl;
		return 0;
	}
	
	char * train, *test = NULL;
	int has_header = 1;
	char delim = ',';


	if(argc >= 2){
		train = argv[1];
		test = argv[2];
	}
	if(argc >= 4){
		has_header = std::stoi(argv[2], nullptr);
	}
	if(argc >= 5){
		delim = argv[3][0];
	}

	std::cout << "running : ./inf442 " << train << " " << test << " has_header=" << has_header << " delim='" << delim << "'" << std::endl;

	int col_regr = 24;
	Dataset train_data(train, has_header, delim);
	Dataset test_data(test, has_header, delim);
	train_data.Show(0);
	test_data.Show(0);

	test_regr_linear<LinearRegressionConstant>(train_data, test_data, col_regr);
	test_regr_linear<LinearRegressionDiagonal>(train_data, test_data, col_regr);
	test_regr_linear<LinearRegression>(train_data, test_data, col_regr);


	return 0;
}
