#include "book_collection.h"
#include "support.h"
#include "book.h"
#include <iostream>
#include <cstdio>

const int init_size = 2; //начальное количество книг в пустой картотеке
const char* names = "names_of_books.txt";


void createLibrary(Library& library) { //создать нулевую картотеку
	library.books = new BOOK*[init_size];
	library.number = 0;
	library.capacity = init_size;
}

bool emptyFile(const char* names) { //является ли файл пустым
	FILE* file;
	if (fopen_s(&file, names, "r") != 0) { //проверка на существование
		printf("Error: Failed to open the file.\n");
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
	int num_of_lines=0;
	char ch;
	while ((ch = fgetc(file)) != EOF) { //пока не дошли до конца файла
		if (ch == '\n') { //если символ конца строки -> +1 строка
			num_of_lines++;
		}
	}
	rewind(file); // перемещаем указатель файла в начало для дальнейшего считывания элементов
	return num_of_lines;
}

void scanBook(FILE* file, BOOK *book) { //сканирует книгу из файла
	fscanf_s(file, "%49s %99s %hd %lf %d\n", book->author, sizeof(book->author), book->title, sizeof(book->title),
		&(book->year), &(book->price), &(book->category));
}

void loadLibrary(Library* library, const char* names) { //загрузить содержимое из файла в картотеку
	FILE* file;
	errno_t err = fopen_s(&file, names, "r"); //проверка на существование
	if (err != 0) {
		printf("Error: this file doesn't exist.");
	}
	else {
		if (emptyFile(names)) {
			printf("This file is empty!");
		}
		else {
			clearLibrary(*library);
			//Чтение данных из файла
			int num_of_elem = countNumberBooks(file); //а) считали количество элементов
			BOOK** books = new BOOK*[num_of_elem]; //б) создали массив требуемой размерности
			int cur_index = 0; //отслеживаем, сколько строк считали
			while (!feof(file) && cur_index < num_of_elem) { //пока не достигли конца файла и загрузили не все элементы
				books[cur_index] = new BOOK;
				scanBook(file, books[cur_index]); //в) считали данные из файла в массив
				cur_index++;
			}
			library->books = books;
			library->number = cur_index;
			library->capacity = num_of_elem;
		}
		fclose(file);
	}
			
}

void clearLibrary(Library &library) { //очистить существующую картотеку (для loadLibrary)
	for (int i = 0; i < library.number; i++) {
		delete library.books[i];
	}
	library.number = 0;
	library.capacity = 0;
}

void printLibrary(const Library& library) { //распечатать содержимое картотеки
	if (library.number != 0) { //если картотека не пуста
		for (int i = 0; i < library.number; i++) {
			const BOOK* book = library.books[i];
			printf("Number of book: %d\n", i + 1);
			printBook(*book);
		}
	}
	else {
		printf("The library is empty!");
	}
}

void appendBook(Library& library) { //добавить новую книгу
	BOOK* newBook = new BOOK();
	initBook(*newBook);
	library.number++;
	library.books[library.number - 1] = newBook;

}

void increaseLibrary(Library& library) { //увеличить размер library
	BOOK** tempbooks = new BOOK * [library.capacity + 1];
	for (int i = 0; i < library.capacity; i++) {
		tempbooks[i] = library.books[i];
	}
	delete[] library.books;
	library.books = tempbooks;
	library.capacity++;
}

void addBook(Library& library) { //добавить новую книгу в картотеку
	if (library.number < library.capacity) {
		appendBook(library); 
		if (library.number == library.capacity) {
			increaseLibrary(library);
		}
	}
		else{
			increaseLibrary(library);
			appendBook(library);
		}
	printTitles(library);
}

void printTitles(const Library& library) {
	for (int i = 0; i < library.number; i++) {
		printf("[%d] %s\n", i + 1, getTitle(*library.books[i]));
	}
}

void deleteBook(Library& library) { //удалить существующую книгу или диапазон книг 
	int indexBook;
	int agreement;
	printf("Are you sure you want to delete the book? It will be impossible to restore it.\n");
	printf("If you really want to delete the book, input 1. Else input 0.\n");
	while (true) {
		scanf_s("%d", &agreement);
		if (agreement == 1) {
			printTitles(library);
			while (true) {
				printf("Enter the number of the book to be deleted: ");
				scanf_s("%d", &indexBook);
				if (indexBook > 0 && indexBook < library.number + 1) {
					delete library.books[indexBook - 1];
					for (int i = indexBook - 1; i < library.number; i++) {
						library.books[i] = library.books[i + 1];
					}
					library.number--;
					printTitles(library);
					break;
				}
				else {
					printf("Sorry, the number of book is wrong! Try again \n");
				}
			}
			break;
		}
		else if (agreement==0){
			printf("Have a nice reading!\n");
			break;
		}
		else {
			printf("This command is wrong. Try again!\n");
			while (getchar() != '\n');
			continue;
		}
	}
}

void scanLibrary() { //записать текущее содержимое картотеки в файл 
	//открывает файл для чтения, очищает текущую картотеку и добавляет каждую книгу из файла в картотеку.
}

int countBookCategory() { //ИЗ: по всей картотеке вычислить, сколько книг относится к категории введенной пользователем
	return 1;
}