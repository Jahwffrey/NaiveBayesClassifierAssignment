#ifndef _TRIE_H
#define _TRIE_H

#include<vector>
#include<string>

using namespace std;

class Trie{
 private:
	char letter;
	vector<Trie *> childs;
	int docs_letters[2];
	int docs_words[2];
	Trie* get_child(char c);
	Trie* make_child(char c);
 public:
	Trie(char c);
	Trie* add_word(string word,int type);
	Trie* get_word(string word);
	void get_type(int type);
	void print(string str);
};

#endif
