//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include "review.h"
using namespace std;

//I HAVE <br /> problems!!!!

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}

	ifstream train_file(argv[1]);

	//Read in lines
	std::string rev;
	while(getline(train_file,rev)){
		//rev.replace(rev.begin(),rev.end(),"<br />"," ");
		int len = rev.length();
		int type = rev[len - 1];
		Review* current = new Review(rev, type);		

		string wrd;
		while(current->next_word(wrd)){
			cout << wrd << endl;
		}

		delete(current);
	}	

	return 1;
}
