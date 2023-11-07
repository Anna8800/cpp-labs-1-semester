#include "support.h"
#include <iomanip>
#include <cstdio>
/*
support -> модуль ввода/вывода
Для файлового ввода/вывода используйте функции fprintf и fscanf.
-первичная поддержка пользователя, readme, переход на дальнейшие функции
Функции ввода/вывода НЕ должны применяться за пределами модуля ввода-вывода. По возможности стараться избегать дублирования кода,
например, код считывающий структуру с клавиатуры и из файла будет практически одинаковым,
подумайте, как организовать функции так, чтобы дублирование было минимально.
*/
void init_readme() {
	printf("Hello! Welcome to our book app. ");
	printf("Possibilities of app:\n");
	printf("[l] - load books from the file to the library;\n");
	printf("[p] - print the library;\n");
	printf("[a] - add new book to the library;\n");
	printf("[d] - delete the book from the library;\n");
	printf("[s] - save library to the file;\n");
	printf("[r] - sort books on the field;\n");
	printf("[b] - count books which relate some category;\n");
	printf("[q] - stop running the program;\n");
	printf("----------------------------\n");
	printf("Enter [letter] to choose the action.\n");
}

// определение правильности выбранного числа книги/книг для удаления
int valid_number(Library& library, int definit, int init_number) { 
	int prob;
	int number;
	while (true) {
		if (scanf_s("%d", &prob) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		if (definit == 1 && prob > 0 && prob < library.number + 1) { // 1 - если удаляем одно число
			number = prob;
			return number;
			break;
		}
		else if (definit == 2 && prob > 0 && (prob + init_number) < library.number + 1) { // 2 - если удаляем диапазон
			number = prob;
			return number;
			break;
		}
		else { //обработка ошибки выхода за границу картотеки
			printf("Error! Too small or too big number of the book. Try again:");
			while (getchar() != '\n');
			continue;
		}
	}
}

void perm_delete(Library& library, int& Number, int& indexBook) { //разрешение на удаление
	int agreement; //передаем по ссылке параметры, которые изменяем
	printf("Are you sure you want to delete the book? It will be impossible to restore it.\n");
	printf("If you really want to delete the book, input 1. If you want to delete range of books, input 2. Else input 0.\n");
	while (true) {
		if (scanf_s("%d", &agreement) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		if (agreement == 1) {
			printTitles(library);
			printf("Enter the number of deleted book: ");
			indexBook = valid_number(library, 1, 0);
			Number = 1;
			break;
		}
		else if (agreement == 2) {
			printTitles(library);
			printf("Enter the first number of the book to be deleted: ");
			indexBook = valid_number(library, 1, 0);
			printf("Enter the amount of deleted book: ");
			Number = valid_number(library, 2, indexBook);
			break;
		}
		else if (agreement == 0) {
			printf("Have a nice reading!\n");
			Number = -1;
			indexBook = -1;
			break;
		}
		else {
			printf("Sorry, the command is wrong! Try again. \n");
			while (getchar() != '\n');
			continue;
		}
	}
}
