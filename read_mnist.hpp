#include <string>
#include <fstream>
#include <vector>

class read_mnist{
	public:
	read_mnist()
	{}

	bool read_images(std::string filename){
		std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);
		if(!fin){
			return false;
		}

		unsigned char int_read_c[4];
		int magic_number; //may useless
		
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		magic_number = charstoint(int_read_c);
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		num = charstoint(int_read_c);
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		row = charstoint(int_read_c);
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		col = charstoint(int_read_c);
		std::cout << desc << std::endl << num << std::endl << row << std::endl << col << std::endl;

		std::vector<unsigned char> read_vector(row*col);
		while(true){
			fin.read(reinterpret_cast<char*>(&(read_vector[0])), sizeof(unsigned char)*row*col);
			if(fin.eof()) break;
			image.push_back(read_vector);
		}
		return true;
	}

	bool read_labels(std::string filename){
		std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);
		if(!fin){
			return false;
		}

		unsigned char int_read_c[4];
		int magic_number; //may useless
		
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		magic_number = charstoint(int_read_c);
		fin.read(reinterpret_cast<char*>(int_read_c), sizeof(int_read_c));
		num = charstoint(int_read_c);

		char read_c;
		while(true){
			fin.read(&read_c, sizeof(read_c));
			if(fin.eof()) break;
			label.push_back(read_c);
		}
		return true;
	}

	std::vector<std::vector<unsigned char> > images(){
		return image;
	}
	std::vector<unsigned char> labels(){
		return label;
	}

	private:
	int desc, num, row, col;
	std::vector< std::vector<unsigned char> > image;
	std::vector< unsigned char > label;

	int charstoint(unsigned char c[4]){
		int ans = (c[0] << 24) + (c[1] << 16) + (c[2] << 8) + c[3];
		return ans;
	}
};

