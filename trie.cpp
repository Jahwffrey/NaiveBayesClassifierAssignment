//John Thomason
//ID 3058344



#include <iostream>
#include <string>
#include "trie.h"
#include <math.h>

using namespace std;

Trie::Trie(char c){
	this->letter = c;
	this->word_count = 0;
	this->word_occurs[0] = 0;
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

Trie* Trie::add_word_root(string word,int type,double value){
	word_nums[type] += value;
	word_count += value;
	add_word(word,type,value);
}

Trie* Trie::add_word(string word,int type,double value){
	//docs_letters[type] += 1;
	if(word.length() == 0){
		word_occurs[type] += value;
		return this;
	} else {
		char c = word[0];
		Trie* t = get_child(c);
		if(t == NULL) t = make_child(c);
		word.erase(word.begin());
		return t->add_word(word,type,value);
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

void Trie::calc_data(int pos_num,int neg_num,int wordnum,double word_nums_p,double word_nums_n){
	if(wordnum == 0){
		wordnum = word_count;
		word_nums_p = word_nums[1];
		word_nums_n = word_nums[0];
	}

	word_nums[1] = word_nums_p;
	word_nums[0] = word_nums_n;
	//if(docs_words[0] != 0) 
	for(int i = 0; i < 2;i++){
		prob[i] = //log ( 
			((double)word_occurs[i] + 1) / 
			((double)word_nums[i] + (double)wordnum + 1)
		;//);
		//cout << word_nums[i] << "!\n";
	}

	//idf
	/*if(word_occurs[1] != 0){
		prob[1] = prob[1] * ( 1 + log2((double)pos_num/(double)word_occurs[1]));
	}
	
	if(word_occurs[0] != 0){
		prob[0] = prob[0] * ( 1 + log2((double)neg_num/(double)word_occurs[0]));
	}*/

	int cutoff = 1000;
	if(word_occurs[0] >= cutoff && word_occurs[1] >= cutoff && fabs(word_occurs[0] - word_occurs[1]) < cutoff){
		prob[0] = 1;
		prob[1] = 1;
	}
	
	for(int i = 0; i < 2;i++){
		prob[i] = log ( prob[i] );
	}

	for(int i = 0;i < childs.size();i++){
		childs[i] -> calc_data(pos_num,neg_num,wordnum,word_nums_p,word_nums_n);
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

double Trie::print_most_important(string str,double max,int type,string ignore){
	str = str + letter;
	if(!(str.compare(ignore) == 0)){
		//double nmax = prob[type] - prob[(type + 1) % 2];
		double nmax = prob[type] - prob[(type + 1) % 2];
		if(nmax > max || max > 4 || nmax > 3.4){
			cout << str << ": " << nmax << "\n";
			max = nmax;
		}
	}
	for(int i = 0;i < childs.size();i++){
		max = childs[i] -> print_most_important(str,max,type,ignore);
	}
	return max;
}
