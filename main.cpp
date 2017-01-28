//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "review.h"
#include "trie.h"
using namespace std;

//I HAVE <br /> problems!!!!
//Consider sorting tries

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
		//rev.replace(rev.begin(),rev.end(),"<br />"," ");
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
