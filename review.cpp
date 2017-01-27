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

bool Review::next_word(string &out){
	out = "";
	if(head >= len) return false;
	while(head < len && text[head] != ' '){
		if(check_char(text[head])) out = out + text[head];
		head++;
	}
	out = out + "!";
	head++;
	return true;
}
