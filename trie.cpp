#include <iostream>
#include <string>
#include "trie.h"
#include <math.h>

using namespace std;

Trie::Trie(char c){
	this->letter = c;
	this->word_count = 0;
	//this->docs_letters[0] = 0;
	this->word_occurs[0] = 0;
	//this->docs_letters[1] = 0;
	this->word_occurs[1] = 0;
	this->prob[0] = 0;
	this->prob[1] = 0;
	this->word_nums[0] = 0;
	this->word_nums[1] = 0;
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

Trie* Trie::add_word_root(string word,int type){
	if(get_word(word) == NULL) word_count += 1;
	add_word(word,type);
}

Trie* Trie::add_word(string word,int type){
	//docs_letters[type] += 1;
	if(word.length() == 0){
		word_occurs[type] += 1;
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

void Trie::calc_data(int pos_num,int neg_num,int wordnum){
	if(wordnum == 0) wordnum = word_count;
	//if(docs_words[0] != 0) 
	prob[0] = log10 ( 
		((double)word_occurs[0] + 1) / 
		((double)neg_num + (double)wordnum + 1)
	);
	//if(docs_words[1] != 0) prob[1] = log10 ( (double)docs_words[1] / (double)pos_num );
	//if(docs_words[1] != 0) 
	prob[1] = log10 ( 
		((double)word_occurs[1] + 1) / 
		((double)pos_num + (double)wordnum + 1)
	);
	for(int i = 0;i < childs.size();i++){
		childs[i] -> calc_data(pos_num,neg_num,wordnum);
	}
}

void Trie::print(string str){
	str = str + letter;
	if(word_occurs[0] != 0 || word_occurs[1] != 0){
		cout << str << " - Words: " << word_occurs[0] << ", " << word_occurs[1] <<"\n";
	}
	for(int i = 0;i < childs.size();i++){
		childs[i] -> print(str);
	}
}

void Trie::print_probs(string str){
	str = str + letter;
	if(word_occurs[0] != 0 || word_occurs[1] != 0){
		cout << str + " - N: " << prob[0] << " P: " << prob[1] << endl;
	}
	for(int i = 0;i < childs.size();i++){
		childs[i] -> print_probs(str);
	}
}

double Trie::get_pos_prob(){
	return prob[1];
}
double Trie::get_neg_prob(){
	return prob[0];
}
