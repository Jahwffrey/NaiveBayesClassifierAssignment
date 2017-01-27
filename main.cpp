#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Review{
 private:
	string text;
	int type;
	int head;
 public:
	bool next_word(string out);
	Review(string txt,int type);
};

Review::Review(string txt,int type){
	this->text = txt;
	this->type = type;
}

bool Review::next_word(string out){
	out = "Wow!";
	return false;
}

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}

	ifstream train_file(argv[1]);

	//Read in lines
	std::string rev;
	while(getline(train_file,rev)){
		int len = rev.length();
		int type = rev[len - 1];
		Review* current = new Review(rev, type);		

		string wrd;
		while(current->next_word(wrd)){
			cout << wrd << endl;
		}
		cout << "Lol" << endl;

		delete(current);
	}	

	return 1;
}
