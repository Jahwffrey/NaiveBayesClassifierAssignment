//John Thomason
//ID 3058344



#include <fstream>
#include <iostream>
#include <string>
#include "review.h"

using namespace std;

bool Review::check_char(char c){
	return(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


Review::Review(string txt){
	this->text = txt;
	this->head = 0;
	this->len = txt.length() - 2;
}

bool Review::next_word(string* outarr, int word_num){
	string out = "";
	if(head >= len) return false;
	int word_count = 0;
	int index = head;
	while(word_count < word_num){
		char c = tolower(text[index]);
		if(c == ' '){
			if(word_count == 0) head = index + 1;
			outarr[word_count] = out;
			word_count += 1;
		}
		if(check_char(c) && word_count < word_num) out = out + c;
		index++;
		if(index == len - 1){
			c = tolower(text[index]);
			word_count = word_num;
			if(check_char(c)) out = out + c;
			outarr[word_count - 1] = out;
			head = index + 1;
		}
	}
	return true;
}
