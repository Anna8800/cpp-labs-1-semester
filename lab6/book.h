#pragma once
#define LEN_AUTHOR 51
#define LEN_TITLE 101

extern const char* category[]; //для исключения множественного определения символов и ошибки линковки
extern const int len_author;
extern const int len_title;
//extern const char names[256];

struct BOOK {
	char author[LEN_AUTHOR];
	char title[LEN_TITLE];
	short year;
	double price;
	int category;
};

void printBook(const BOOK& book); 
void initBook(BOOK& book);
char* getTitle(BOOK& book); 
void printBookCategory();
void str_input(char* str, int& choice, const int allowed_length);
void enterName(char* names);
//void str_input(std::string& str, int& choice, const int allowed_length);