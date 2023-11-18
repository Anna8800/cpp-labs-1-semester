#include "support.h"
#include "sort.h"
#include <iomanip>
#include <cstdio>

void init_readme() {
	printf("Possibilities of app:\n");
	printf("[l] - load books from the file to the library;\n");
	printf("[p] - print the library;\n");
	printf("[t] - print titles of the library;\n");
	printf("[a] - add new book to the library;\n");
	printf("[d] - delete the book from the library;\n");
	printf("[s] - save library to the file;\n");
	printf("[r] - sort books on the field;\n");
	printf("[b] - count books which relate some category;\n");
	printf("[q] - stop running the program;\n");
	printf("[h] - get help;\n");
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
		else if (definit == 2 && prob > 0 && (prob - init_number+1) < library.number + 1 && prob < library.number + 1) { // 2 - если удаляем диапазон
			number = prob;
			return number;
			break;
		}
		else { //обработка ошибки выхода за границу картотеки
			printf("Error! Too small or too big number of the book. Try again: ");
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
			while (true) {
				indexBook = valid_number(library, 1, 0);
				if (indexBook >= library.number) {
					printf("Error! You can't delete the range of books. Please input a smaller number: ");
					while (getchar() != '\n');
					continue;
				}
				else {
					break;
				}
			}
			printf("Enter the last number of the book to be deleted: ");
			while (true) {
				int lastBook = valid_number(library, 2, indexBook);
				if (lastBook < indexBook) {
					printf("Error! The last book number cannot be smaller than the first book number. Please enter the correct last number: ");
					while (getchar() != '\n');
					continue;
				}
				else {
					Number = lastBook - indexBook + 1;
					break;
				}
			}
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

void input_category(int& categor) {
	printf("Choose the category: \n");
	printBookCategory();
	while (true){
		if (scanf_s("%d", &categor) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			int numCategories = getNumCategories(category);
			if (categor > 0 && categor <= numCategories) {
				break;
			}
			else {
				printf("Wrong value of category! Try again: ");
				while (getchar() != '\n');
				continue;
			}
		}
	}
}

int getNumCategories(const char* arr[]) {
	int count = 0;
	while (arr[count] != NULL) {
		count++;
	}
	return count;
}

void warning_empty_file() {
	printf("This file is empty!\n");
}
void warning_empty_library() {
	printf("This library is empty! Please, load books from the file to the library\n");
}
void warning_existence_check() {
	printf("Error: this file doesn't exist.\n");
}

void choise_field_to_sort(Library& library) {
	if (library.number != 0) {
		printf("Please, choose type of sorting:\n");
		printf("1 - by author, 2 - by title, 3 - by year, 4 - by price, 5 - by category\n");
		printf("Enter the number of type: ");
		int comp = 0;
		while (true) {
			if (scanf_s("%d", &comp) != 1) { // проверяем успешность считывания значения
				printf("Invalid input. Please enter a valid number: ");
				while (getchar() != '\n');
				continue;
			}
			else {
				if (comp >= 0 && comp < 6) {
					break;
				}
				else {
					printf("Wrong value of sorting type! Try again: ");
					while (getchar() != '\n');
					continue;
				}
			}
		}
		sortLibrary(library, comparator[comp - 1]);
	}
	else {
		warning_empty_library();
	}
}

void recent_files(const char names[256], const char* filename) { //последние файлы
	const int maxNames = 3; //храним только три последних
	char existingNames[maxNames][256]; //максимально возможный размер имени файла
	int numExistingNames = 0; 
	FILE* file;
	if (fopen_s(&file, filename, "r+") != 0){
		printf("Error opening file for reading and writing.\n");
		return;
	}
	for (int i = 0; i < maxNames; i++) { //записать содержимое в массив
		if (fscanf_s(file, "%255s", existingNames[i], sizeof(existingNames[i])) == EOF) {
			break;
		}
		numExistingNames++;
	}
	bool isExisting = false; //проверим на наличие этого названия в списке
	int existingIndex = -1;
	for (int i = 0; i < numExistingNames; i++) {
		if (strcmp(names, existingNames[i]) == 0) {
			isExisting = true;
			existingIndex = i;
			break;
		}
	}
	if (isExisting) { //если новое значение уже существует, удаляем его из текущего положения
		for (int i = existingIndex; i < numExistingNames - 1; i++) {
			strcpy_s(existingNames[i], sizeof(existingNames[i]), existingNames[i + 1]);
		}
		numExistingNames--;
	}
	if (numExistingNames >= maxNames) { //если количество значений превышает max, удаляем последнее значение
		numExistingNames--;
	}
	for (int i = numExistingNames; i > 0; i--) {
		strcpy_s(existingNames[i], sizeof(existingNames[i]), existingNames[i - 1]);
	}
	strcpy_s(existingNames[0], sizeof(existingNames[0]), names);
	numExistingNames++;
	rewind(file);
	for (int i = 0; i < numExistingNames; i++) {
		fprintf(file, "%s\n", existingNames[i]);
	}
	fclose(file);
}

void print_recent(const char* filename) {
	FILE* file;
	errno_t err = fopen_s(&file, filename, "r");
	if (err != 0) {
		printf("Error opening file for reading.\n");
		return;
	}
	printf("Your recent files: \n");
	char value[256];
	while (fscanf_s(file, "%255s", value, sizeof(value)) != EOF) {
		printf("%s\n", value);
	}
	fclose(file);
}
