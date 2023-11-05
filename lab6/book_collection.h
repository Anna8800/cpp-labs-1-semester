#pragma once
#include "book.h"  
#include <iostream>

struct Library {
	BOOK** books;
	int number; //количество книг в картотеке
	int capacity; //емкость массива
};

//Считать из файла содержимое в картотеку -> разве не автоматически при создании картотеки?

void createLibrary(Library &library);
bool emptyFile(const char* names_of_books);
int countNumberBooks(FILE *file);
void scanBook(FILE* file, BOOK* Book);
void loadLibrary (Library* library, const char* names_of_books); 
void clearLibrary(Library& library); 
void printLibrary(const Library& Library);
void appendBook(Library& library);
void increaseLibrary(Library& library);
void addBook(Library& library); 
void printTitles(const Library& library);
void deleteBook(Library& library); 
void scanLibrary(); //не сделана
int countBookCategory(); //не сделана
//sort по любому из полей