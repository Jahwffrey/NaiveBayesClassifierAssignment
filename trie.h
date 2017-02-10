//John Thomason
//ID 3058344



#ifndef _TRIE_H
#define _TRIE_H

#include<vector>
#include<string>

using namespace std;

class Trie{
 private:
	char letter;
	vector<Trie *> childs;
	double word_count;
	double word_occurs[2];
	double word_nums[2];
	double prob[2];
	Trie* get_child(char c);
	Trie* make_child(char c);
 public:
	Trie(char c);
	Trie* add_word_root(string word,int type,double value);
	Trie* add_word(string word,int type,double value);
	Trie* get_word(string word);
	void get_type(int type);
	void print(string str);
	void print_probs(string str);
	double print_most_important(string str,double max,int type,string ignore);
	void calc_data(int pos_num,int neg_num,int word_num,double word_nums_p,double word_nums_n);
	double get_pos_prob();
	double get_neg_prob();
};

#endif
