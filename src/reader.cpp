#include "reader.hpp"

csv::csv(char * filename_, int has_header, char delim){
	filename = string(filename_);
	std::ifstream fin(filename);
	if (fin.fail()) {
		std::cout<<"Cannot read from filename "<<filename<<" !"<<std::endl;
		exit(1);

	}
	std::vector<string> tmp; 
	std::vector<string> head;
	int ncols = 0;
    string line, word; 
	
	if(has_header){
		getline(fin, line);
		std::stringstream s(line);
		while (getline(s, word, delim)) { 
			head.push_back(word);
			ncols++;
		}
		m_dim = ncols;
	}

	while (getline(fin, line)) {
		ncols = 0;
        std::stringstream s(line);
        while (getline(s, word, delim)) { 
            tmp.push_back(word);
            ncols++;
        }
        if (m_dim==-1) m_dim = ncols;
        else if (m_dim!=ncols) {
        	std::cerr << "ERROR, inconsistent dataset" << std::endl;
        	exit(-1);
        }
		m_nsamples ++;
	}
	fin.close();

	if(! has_header){
		for(unsigned i = 0; i < m_dim; ++i) {
			string name = string("col") + std::to_string(i);
			head.push_back(name);
		}
	}
	headers = Eigen::Map<VectorXs> (head.data(), head.size());
	m_instances = Eigen::Map<MatrixXs> (tmp.data(),m_nsamples, m_dim);
}


std::ostream& csv::print (std::ostream &out){
	out << "Csv issu de " << filename << std::endl;
	out << "Nombre d'instance : " << m_nsamples << std::endl;
	out << "Nombre de colonnes : " << m_dim << std::endl;
	out << headers << std::endl << std::endl;
	//out << m_instances << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream &out, csv &b){
	return b.print(out);
}

int csv::nb_cols(){
	return m_dim;
}

unsigned long csv::nb_lines(){
	return m_nsamples;
}

VectorXs csv::get_headers(){
	return headers;
}

int csv::get_col_index(string head){
	auto it = std::find(headers.begin(), headers.end(), head);
	if(it == headers.end()){
		std::cerr << "ERROR, header : " << head << " doesn't exist" << std::endl;
		return -1;
	}
	int ind = it - headers.begin();
	return ind;
}

VectorXs csv::get_line(unsigned long i){
	if(i >= m_nsamples || i < 0)
		std::cerr << "ERROR, get_line : " << i << " is wrong" << std::endl;
	return m_instances.row(i);
}

VectorXs csv::get_cols(int i){
	if(i >= m_dim || i < 0)
		std::cerr << "ERROR, get_cols : " << i << " is wrong" << std::endl;
	return m_instances.col(i);
}

VectorXs csv::get_cols(string head){
	int ind = get_col_index(head);
	return get_cols(ind);
}

