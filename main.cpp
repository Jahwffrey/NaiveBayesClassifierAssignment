#include <fstream>
#include <iostream>
using namespace std;

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}
	cout << "Hello world!\n";
	return 1;
}
