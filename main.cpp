//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "review.h"
using namespace std;

//I HAVE <br /> problems!!!!
//Consider sorting tries

class Trie{
 private:
	char letter;
	vector<Trie *> childs;
	int docs[2];
	Trie* get_child(char c);
	Trie* make_child(char c);
 public:
	Trie(char c);
	Trie* add_word(string word,int type);
	Trie* get_word(string word);
	void add_type(int type);
};

Trie::Trie(char c){
	this->letter = c;
	this->docs[0] = 0;
	this->docs[1] = 0;
}

Trie* Trie::get_child(char c){
	for(int i = 0;i < childs.size();i++){
		if(childs[i]->letter == c) return childs[i];
	}
	return NULL;
}

Trie* Trie::make_child(char c){
	Trie* new_trie = new Trie(c);
	childs.push_back(new_trie);
	return new_trie;
}

Trie* Trie::add_word(string word,int type){
	
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

	//Read in lines
	std::string rev;
	while(getline(train_file,rev)){
		//rev.replace(rev.begin(),rev.end(),"<br />"," ");
		int len = rev.length();
		int type = rev[len - 1];
		docs[type] += 1;
		Review* current = new Review(rev, type);		

		string wrd;
		while(current->next_word(wrd,1)){
			cout << wrd << "!" << endl;
		}

		delete(current);
	}	

	return 1;
}
