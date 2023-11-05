#pragma once
extern const char* category[]; //для исключения множественного определения символов и ошибки линковки

struct BOOK {
	char author[50];
	char title[100];
	short year;
	double price;
	int category;
};

void printBook(const BOOK& book);
void initBook(BOOK& book);
char* getTitle(BOOK& book);
