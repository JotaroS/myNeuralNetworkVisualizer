#include <iostream>
#include "read_mnist.hpp" 

//Sample program for read_mnist.
int main(int argc, char** argv){
	read_mnist c1;

	//read database(read train images/labels here.)
	if(!c1.read_images("train-images.idx3-ubyte")){
		std::cout << "Could Not Read Image File!" << std::endl;
		return -1;
	}
	if(!c1.read_labels("train-labels.idx1-ubyte")){
		std::cout << "Could Not Read Label File!" << std::endl;
		return -1;
	}

	//images() returns image files
	//example: image[0][0] is 1st pixel datum of 1st image
	//example: image[1][20] is 20th pixel datum of 2nd image
	std::vector<std::vector<unsigned char> >image = c1.images();
	std::vector<unsigned char>label = c1.labels();

	//output sample
	for(int i = 0; i < label.size(); i++){
		std::cout << i << ": " <<  (int)label.at(i) << std::endl;
	}
	return 0;
}

