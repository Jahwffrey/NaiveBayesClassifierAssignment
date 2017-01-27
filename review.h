#ifndef _REVIEW_H
#define _REVIEW_H

#include <string>

class Review{
 private:
	std::string text;
	int type;
	int head;
	int len;
	bool check_char(char c);
 public:
	bool next_word(std::string &out);
	Review(std::string txt,int type);
};

#endif
