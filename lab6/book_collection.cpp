﻿#include "book_collection.h"
#include "support.h"
#include "book.h"
#include "sort.h"
#include "vld.h"
#include <iostream>
#include <cstdio>

const int init_size = 0; //начальное количество книг в пустой картотеке


void createLibrary(Library& library) { //создать нулевую картотеку
	library.books = new BOOK * [init_size];
	library.number = 0;
	library.capacity = init_size;
}

bool emptyFile(const char* names) { //является ли файл пустым
	FILE* file;
	if (fopen_s(&file, names, "r") != 0) { //проверка на существование
		warning_existence_check();
		return false;
	}
	int ch = fgetc(file); //считываем по одному символу из файла
	if (ch == EOF) { //если первый символ = символ конца файла, то файл пустой
		fclose(file);
		return true;
	}
	fclose(file);
	return false;
}

int countNumberBooks(FILE* file) { //считать количество элементов в файле
	int num_of_lines = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF) { //пока не дошли до конца файла
		if (ch == '\n') { //если символ конца строки -> +1 строка
			num_of_lines++;
		}
	}
	rewind(file); // перемещаем указатель файла в начало для дальнейшего считывания элементов
return num_of_lines;
}

void scanBook(FILE* file, BOOK* book) { //сканирует книгу из файла
	fscanf_s(file, "%50[^\t] %99[^\t] %hd %lf %d\n", book->author, sizeof(book->author) - 1, book->title, sizeof(book->title) - 1,
		&(book->year), &(book->price), &(book->category));
}

void loadLibrary(Library* library, const char* names) { //загрузить содержимое из файла в картотеку
	FILE* file;
	errno_t err = fopen_s(&file, names, "r"); //проверка на существование
	if (err != 0) {
		warning_existence_check();
	}
	else {
		if (emptyFile(names)) {
			warning_empty_file();
		}
		else {
			//Чтение данных из файла
			int num_of_elem = countNumberBooks(file); //а) считали количество элементов
			int cur_index = library->number; //индекс, с которого начнется добавление новых книг
			BOOK** new_books = new BOOK * [num_of_elem + cur_index]; //б) создали массив требуемой размерности
			for (int i = 0; i < cur_index; i++) { // копируем существующие книги во временный массив
				new_books[i] = library->books[i];
			}
			int temp = cur_index;
			while (cur_index < num_of_elem + temp && !feof(file)) { //пока не достигли конца файла и загрузили не все элементы
				new_books[cur_index] = new BOOK;
				scanBook(file, new_books[cur_index]); //в) считали данные из файла в массив
				cur_index++;
			}
			library->capacity = cur_index + num_of_elem;
			delete[] library->books;
			library->books = new_books;
			library->number = cur_index;
			printf("Loading is completed\n");
		}
		
		fclose(file);
	}
}

void clearLibrary(Library& library) { //очистить существующую картотеку
	for (int i = 0; i < library.number; i++) {
		delete library.books[i];
	}
	library.number = 0;
	library.capacity = 0;
	delete[] library.books;
	//library.books = nullptr;
}


void printLibrary(const Library& library) { //распечатать содержимое картотеки
	if (library.number != 0) { //если картотека не пуста
		printf("Library contents:\n");
		for (int i = 0; i < library.number; i++) {
			const BOOK* book = library.books[i];
			printf("Number of book: %d\n", i + 1);
			printBook(*book);
		}
	}
	else {
		warning_empty_library();
	}
}

void appendBook(Library& library) { //добавить новую книгу
	BOOK* newBook = new BOOK();
	initBook(*newBook);
	if (strlen(newBook->title) == 0 or strlen(newBook->author) == 0) {
		delete newBook; // Освобождаем память, выделенную для новой книги
		return;
	}
	else {
		library.number++;
		library.books[library.number - 1] = newBook;
	}
}

void increaseLibrary(Library& library) {
	BOOK** tempbooks = new BOOK * [library.capacity + 1];
	for (int i = 0; i < library.capacity; i++) {
		tempbooks[i] = library.books[i];
	}
	delete[] library.books;
	library.capacity++;
	library.books = tempbooks;
}

void decreaseLibrary(Library& library) {
	if (library.number > 0) {
		delete library.books[library.number - 1]; // Освобождаем память, выделенную для последней книги
		library.number--;
		library.capacity--;
	}
}

void addBook(Library& library) { //добавить новую книгу в картотеку
	if (library.number < library.capacity) {
		appendBook(library);
		if (library.number == library.capacity) {
			increaseLibrary(library);
		}
	}
	else {
		increaseLibrary(library);
		appendBook(library);
		if (library.books[library.number - 1] == nullptr){
			decreaseLibrary(library);
		}
	}
	printTitles(library);
}

void printTitles(const Library& library) { //напечатать названия книг
	if (library.number != 0) {
		for (int i = 0; i < library.number; i++) {
			printf("[%d] %s\n", i + 1, getTitle(*library.books[i]));
		}
	}
	else {
		warning_empty_library();
	}
}

void deleteBook(Library& library) { //удалить существующую книгу или диапазон книг 
	if (library.number != 0) {
		int indexBook;
		int Number;
		perm_delete(library, Number, indexBook);
		if (indexBook > 0 && indexBook < library.number + 1) {
			for (int i = indexBook - 1; i < indexBook - 1 + Number; i++) { //удаление
				delete library.books[i];
			}
			for (int i = indexBook - 1 + Number; i < library.number; i++) { //смещение номеров оставшихся книг
				library.books[i - Number] = library.books[i];
			}
			library.number -= Number;
			printTitles(library);
		}
	}
	else {
		warning_empty_library();
	}
}

void scanLibrary(Library* library, const char* names) { //записать текущее содержимое картотеки в файл 
	FILE* file;
	errno_t err = fopen_s(&file, names, "w"); //проверка на существование
	if (err != 0) {
		warning_existence_check();
	}
	else {
		if (library->number == 0) {
			warning_empty_library();
		}
		else {
			for (int i = 0; i < library->number; i++) {
				BOOK* book = library->books[i];
				fprintf(file, "%s\t%s\t%hd\t%.2lf\t%d\n", book->author, book->title, book->year, book->price, book->category);
			}
			printTitles(*library);
		}
		fclose(file);
	}
}

void countBookCategory(Library* library, const char* names) { //ИЗ: по всей картотеке вычислить, сколько книг относится к категории введенной пользователем
	int count = 0;
	int categor;
	if (library->number == 0) {
		warning_empty_library();
	}
	else {
		input_category(categor);
		categor--;
		for (int i = 0; i < library->number; i++) {
			BOOK* book = library->books[i];
			if (book->category == categor) {
				count++;
			}
		}
		printf("%d\n", count);
	}
}