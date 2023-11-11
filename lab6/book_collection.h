#pragma once
#include "book.h"  
#include <iostream>

struct Library {
	BOOK** books;
	int number; //количество книг в картотеке
	int capacity; //емкость массива
};


void createLibrary(Library &library); //+
bool emptyFile(const char* names_of_books); //+
int countNumberBooks(FILE *file); //+
void scanBook(FILE* file, BOOK* Book); //+
void loadLibrary (Library* library, const char* names_of_books); //сделать выбор файла (ввод пользователя) + support 
void clearLibrary(Library& library); //+
void printLibrary(const Library& Library); //+
void appendBook(Library& library); //+
void increaseLibrary(Library& library); //+
void addBook(Library& library); //+
void printTitles(const Library& library);
void deleteBook(Library& library); //+
void scanLibrary(Library* library, const char* names); //+ 
void countBookCategory(Library* library, const char* names); //+