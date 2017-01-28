//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "review.h"
#include "trie.h"
using namespace std;

//Consider sorting tries

void remove_br(string &str){
	for(int i = 0;i < str.length();i++){
		if(str[i] == '<'){
			//if(str.length() - i > 6){
				if(str[i + 1] == 'b' && str[i + 2] == 'r'){
					str.erase(i,5);
				}
			//}
		}
	}
}

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}

	ifstream train_file(argv[1]);
	int docs[2];
	docs[0] = 0;
	docs[1] = 0;
	Trie* trie = new Trie('_');

	//Read in lines
	std::string rev;
	while(getline(train_file,rev)){
		remove_br(rev);
		int len = rev.length();
		int type = rev[len - 1] -'0';
		docs[type] += 1;
		Review* current = new Review(rev, type);		

		string wrd;
		while(current->next_word(wrd,1)){
			trie -> add_word(wrd,type);
		}

		delete(current);
	}	

	trie->print("");

	return 1;
}
