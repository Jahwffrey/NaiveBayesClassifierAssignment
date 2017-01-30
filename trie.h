#ifndef _TRIE_H
#define _TRIE_H

#include<vector>
#include<string>

using namespace std;

class Trie{
 private:
	char letter;
	vector<Trie *> childs;
	int word_count;
	int docs_letters[2];
	int docs_words[2];
	double prob[2];
	Trie* get_child(char c);
	Trie* make_child(char c);
 public:
	Trie(char c);
	Trie* add_word_root(string word,int type);
	Trie* add_word(string word,int type);
	Trie* get_word(string word);
	void get_type(int type);
	void print(string str);
	void print_probs(string str);
	void calc_data(int pos_num,int neg_num,int word_num);
	double get_pos_prob();
	double get_neg_prob();
};

#endif
