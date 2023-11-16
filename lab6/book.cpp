#include "book.h"
//using namespace std;
#include <iostream>

const char* category[] = {
	"Classic",
	"Science fiction",
	"Fairy tale",
	"Short stories",
	"Educational Literature",
	"erge",
};

const int len_author = 51;
const int len_title = 101;
const int max_input_length = 301; 
//char input[max_input_length + 1];

void printBook(const BOOK& book) { //распечатать книгу
	printf("Author: %s\n", book.author);
	printf("Title: %s\n", book.title);
	printf("Year: %hd\n", book.year);
	printf("Price: %.2lf\n", book.price);
	printf("Category: %s\n", category[book.category]);
	printf("\n");
}

void str_input(char* str, int& choice, const int allowed_length) {
	char input[max_input_length];
	scanf_s(" %300[^\n]", input, max_input_length);
	input[max_input_length - 1] = '\0';

	if (strlen(input) > allowed_length) {
		printf("The entered text is too long. Please choose one of the options:\n");
		printf("If you want to enter a new text, input 1.\n");
		printf("If you want this text cutted to %d characters, input 2.\n", allowed_length);
		printf("If you want to cancel entering the text, input 3.\n");
		printf("Enter your choice: ");

		while (true) {
			if (scanf_s("%d", &choice) != 1) {
				printf("Invalid input. Please enter a valid number: ");
				while (getchar() != '\n');
				continue;
			}
			else {
				if (choice == 1) {
					printf("Enter text (you have only %d symbols!): ", allowed_length);
					while (getchar() != '\n');
					scanf_s(" %300[^\n]", input, max_input_length);
					input[allowed_length-1] = '\0';
					break;
				}
				else if (choice == 2) {
					input[allowed_length - 1] = '\0'; // Обрезаем строку до allowed_length - 1 символов
					break;
				}
				else if (choice == 3) {
					printf("Entering the text canceled.\n");
					break;
				}
			}
		}
	}

	if (choice != 3) {
		strcpy_s(str, allowed_length, input);
	}

	while (getchar() != '\n');
}


void initBook(BOOK& book) { //добавить книгу
	int choice;
	printf("Enter author of the book (you have only 50 symbols!): ");
	str_input(book.author, choice, len_author - 1);
	if (choice == 3) {
		return;
	}
	choice = 0;
	printf("Enter title of the book (you have only 100 symbols!): ");
	str_input(book.title, choice, len_title - 1);
	if (choice == 3) {
		return;
	}
	short year_n;
	printf("Enter year of publishing: ");
	while (true) {
		if (scanf_s("%hd", &year_n) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			if ((year_n < -6000) || (year_n > 2023)) {
				printf("Error! Too small or too big year of publishing. Try again: ");
				while (getchar() != '\n');
				continue;
			}
			else {
				book.year = year_n;
				break;
			}
		}
	}

	double price_n;
	printf("Enter price of the book: ");
	while (true) {
		if (scanf_s("%lf", &price_n) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			if (price_n <= 0) {
				printf("Error! Too small price. Try again:");
				while (getchar() != '\n');
				continue;
			}
			else {
				book.price = price_n;
				break;
			}
		}
	}

	int categor_n;
	printBookCategory();
	while (true) {
		if (scanf_s("%d", &categor_n) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			int numCategories = sizeof(category) / sizeof(category[0]);
			if (categor_n > 0 && categor_n <= numCategories){
				book.category = categor_n-1;
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

char* getTitle(BOOK& book) { //напечатать оглавления
	return book.title;
}

void printBookCategory() {
	int numCategories = sizeof(category) / sizeof(category[0]);
	printf("Enter category of the book: (");
	for (int i = 0; i < numCategories; i++) {
		printf("%d - %s", i + 1, category[i]);
		if (i != numCategories - 1) {
			printf(", ");
		}
	}
	printf("): ");
}