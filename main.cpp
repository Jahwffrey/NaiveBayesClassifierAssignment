//John Thomason
//ID 3058344

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "review.h"
#include "trie.h"
#include <ctime>

#define WORDNUM 3
#define FIRSTWORD 1
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

void train(char* train_file_name,Trie* trie,int* docs){
	std::string rev;
	ifstream train_file(train_file_name);
	while(getline(train_file,rev)){
		remove_br(rev);
		int len = rev.length();
		int type = rev[len - 1] -'0';
		docs[type] += 1;
		Review* current = new Review(rev);		

		string wrd[WORDNUM];
		while(current->next_word(wrd,WORDNUM)){
			/*cout << "[";
			for(int i = 0;i < WORDNUM;i++){
				cout << wrd[i] << ",";
			}
			cout << "]\n";*/
			for(int i = FIRSTWORD; i < WORDNUM;i++){
				trie -> add_word_root(wrd[i],type, 1);
			}
		}

		delete(current);
	}

	trie->calc_data(docs[1],docs[0],0,0,0);
}

void test(char * test_file_name,Trie* trie,int* docs,int& correct_num,int& incorrect_num,bool prnt){
	std::string rev;
	ifstream test_file(test_file_name);
	while(getline(test_file,rev)){
		remove_br(rev);
		int len = rev.length();
		
		//Extracting for now, not used in classifying
		int type = rev[len - 1] -'0';
		Review* current = new Review(rev);		

		double pos_prob = 0;
		double neg_prob = 0;
		string wrd[WORDNUM];

		//classify
		while(current->next_word(wrd,WORDNUM)){
			for(int i = FIRSTWORD;i < WORDNUM;i++){
				Trie* data = trie->get_word(wrd[i]);
				if(data != NULL){
					pos_prob += data->get_pos_prob();
					neg_prob += data->get_neg_prob();
				}
			}
		}

		int most_probable_type = 0;
		if(pos_prob > neg_prob) most_probable_type = 1;
		if(prnt){
			cout << "P: " << pos_prob << ", N: " << neg_prob << " = ";
			cout << most_probable_type << endl;
		}

		if(most_probable_type == type){
			correct_num += 1;
		} else {
			incorrect_num += 1;
		}

		delete(current);
	}
}

int main(int argc,char** argv){
	if(argc != 3){
		cout << "Usage: ./NaiveBayesClassifier <file1> <file2>\n";
		return 0; 
	}

	int correct_num = 0;
	int incorrect_num = 0;
	double test_perc;
	double test_2_perc;
	
	int docs[2];
	docs[0] = 0;
	docs[1] = 0;
	Trie* trie = new Trie('_');

	clock_t train_start;
	clock_t train_end;
	clock_t test_end;
	clock_t test_2_end;
	

	//Train
	train_start = clock();	
	train(argv[1],trie,docs);
	train_end = clock();

	//Test
	test(argv[2],trie,docs,correct_num,incorrect_num,true);
	test_perc = 100 * (double)correct_num / (double)(correct_num + incorrect_num);
	correct_num = 0;
	incorrect_num = 0;
	test_end = clock();
	
	//Test against training dataset
	test(argv[1],trie,docs,correct_num,incorrect_num,false);
	test_2_perc = 100 * (double)correct_num / (double)(correct_num + incorrect_num);
	test_2_end = clock();

	cout << (train_end - train_start)/(double)CLOCKS_PER_SEC << " seconds (training)\n";
	cout << (test_2_end - train_end)/(double)CLOCKS_PER_SEC << " seconds (labeling)\n";
	cout << test_2_perc << " (training)\n";
	cout << test_perc << " (testing)\n";

	return 1;
}
