#include <iostream>
#include <cmath>

#include "./reader.hpp"

int main(int argc, char **argv)
{
	if(argc == 2 && strcmp(argv[1] ,"help") == 0 || argc > 4 || argc < 2){
		std::cout << "./inf442 input.csv [has_header=1] [delim=',']" << std::endl;
		return 0;
	}
	
	char * file = NULL;
	int has_header = 1;
	char delim = ',';


	if(argc >= 2){
		file = argv[1];
	}
	if(argc >= 3){
		has_header = std::stoi(argv[2], nullptr);
	}
	if(argc >= 4){
		delim = argv[3][0];
	}

	std::cout << "running : ./inf442 " << file << " has_header=" << has_header << " delim='" << delim << "'" << std::endl;


	csv traffic14(file, has_header, delim);
	traffic14.print(std::cout);


	return 0;
}
