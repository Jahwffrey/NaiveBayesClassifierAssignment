#include <fstream>
#include <iostream>
#include <string>
#include "review.h"

using namespace std;

bool Review::check_char(char c){
	switch(c){
		case '!':
		case '.':
		case ',':
		case '?':
		case '>':
		case '<':
		case '/':
		case '(':
		case ')':
		case ':':
		case ';':
		case '"':
			return false;
		default:
			return true;
	}
}


Review::Review(string txt,int type){
	this->text = txt;
	this->type = type;
	this->head = 0;
	this->len = txt.length() - 2;
}

bool Review::next_word(string &out, int word_num){
	out = "";
	if(head >= len) return false;
	int word_count = 0;
	int index = head;
	while(word_count < word_num){
		char c = text[index];
		if(c == ' '){
			if(word_count == 0) head = index + 1;
			word_count += 1;
		}
		if(check_char(c) && word_count < word_num) out = out + c;
		index++;
		if(index == len - 1){
			word_count = word_num;
			if(check_char(text[index])) out = out + text[index];
			head = index + 1;
		}
	}
	return true;
}
