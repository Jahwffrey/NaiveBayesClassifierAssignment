//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "review.h"
#include "trie.h"

#define WORDNUM 3
using namespace std;

//Consider sorting tries
//Push to github!!


void remove_br(string &str){
	for(int i = 0;i < str.length();i++){
		if(str[i] == '<'){
			if(str.length() - i > 6){
				if(str[i + 1] == 'b' && str[i + 2] == 'r'){
					str.erase(i,5);
				}
			}
		}
	}
}

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}

	ifstream train_file(argv[1]);
	ifstream test_file(argv[2]);
	int correct_num = 0;
	int incorrect_num = 0;
	
	int docs[2];
	docs[0] = 0;
	docs[1] = 0;
	Trie* trie = new Trie('_');

	//Train
	std::string rev;
	while(getline(train_file,rev)){
		remove_br(rev);
		int len = rev.length();
		int type = rev[len - 1] -'0';
		docs[type] += 1;
		Review* current = new Review(rev, type);		

		string wrd;
		while(current->next_word(wrd,WORDNUM)){
			trie -> add_word(wrd,type);
		}

		delete(current);
	}

	trie->calc_data(docs[1],docs[0],0);
	//trie->print_probs("");

	//Validate
		//Nothing!

	//Test
	while(getline(test_file,rev)){
		remove_br(rev);
		int len = rev.length();
		
		//Extracting for now, not used in classifying
		int type = rev[len - 1] -'0';
		Review* current = new Review(rev, type);		

		double pos_prob = 0;
		double neg_prob = 0;
		string wrd;

		//classify
		while(current->next_word(wrd,WORDNUM)){
			Trie* data = trie->get_word(wrd);
			if(data != NULL){
				pos_prob += data->get_pos_prob();
				neg_prob += data->get_neg_prob();
			}
		}

		int most_probable_type = 0;
		if(pos_prob > neg_prob) most_probable_type = 1;

		cout << "P: " << pos_prob << ", N: " << neg_prob << " -> " << most_probable_type << " vs " << type << "\n";

		if(most_probable_type == type){
			correct_num += 1;
		} else {
			incorrect_num += 1;
		}

		delete(current);
	}

	cout << "Success Percentage: " << 100 * (double)correct_num / (double)(correct_num + incorrect_num) << "\n";

	return 1;
}
