#ifndef _REVIEW_H
#define _REVIEW_H

#include <string>

class Review{
 private:
	std::string text;
	int head;
	int len;
	bool check_char(char c);
 public:
	bool next_word(std::string &out,int word_num);
	Review(std::string txt);
};

#endif
