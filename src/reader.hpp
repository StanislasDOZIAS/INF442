#pragma once

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <Eigen/Core>

using std::string;

typedef Eigen::Matrix<string, Eigen::Dynamic, Eigen::Dynamic> MatrixXs;
typedef Eigen::RowVector<string, Eigen::Dynamic> VectorXs;


class csv{
    private :
        unsigned long m_nsamples = 0;
        int m_dim = -1;
        string filename;
        VectorXs headers;
        MatrixXs m_instances;
    
    public :
        csv(char * filename_, int has_header = 1, char delim=',');
        ~csv(){}

        friend std::ostream& operator<<(std::ostream &out, const csv &b);

        std::ostream& print(std::ostream &out);

        int nb_cols();
        unsigned long nb_lines();
        VectorXs get_headers();

        int get_col_index(string head);


        VectorXs get_line(unsigned long i);
        VectorXs get_cols(int i);
        VectorXs get_cols(string head);

};