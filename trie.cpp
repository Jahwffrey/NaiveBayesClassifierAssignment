#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

Trie::Trie(char c){
	this->letter = c;
	this->docs_letters[0] = 0;
	this->docs_words[0] = 0;
	this->docs_letters[1] = 0;
	this->docs_words[1] = 0;
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
	docs_letters[type] += 1;
	if(word.length() == 0){
		docs_words[type] += 1;
		return this;
	} else {
		char c = word[0];
		Trie* t = get_child(c);
		if(t == NULL) t = make_child(c);
		word.erase(word.begin());
		return t->add_word(word,type);
	}
}

Trie* Trie::get_word(string word){
	if(word.length() == 0) return this;
	char c = word[0];
	Trie* t = get_child(c);
	if(t == NULL) return NULL;
	word.erase(word.begin());
	return t->get_word(word);
}

void Trie::print(string str){
	str = str + letter;
	cout << str << " - Words: " << docs_words[0] << ", " << docs_words[1] << " Letters: " << docs_letters[0] << ", " << docs_letters[1] << "\n";
	for(int i = 0;i < childs.size();i++){
		childs[i] -> print(str);
	}
}
