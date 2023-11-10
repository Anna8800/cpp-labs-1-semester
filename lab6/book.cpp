#include "book.h"
using namespace std;
#include <iostream>

const char* category[] = {
	"Classic",
	"Science fiction",
	"Fairy tale",
	"Short stories",
	"Educational Literature"
};

void printBook(const BOOK& book) { //распечатать книгу
	printf("Author: %s\n", book.author);
	printf("Title: %s\n", book.title);
	printf("Year: %hd\n", book.year);
	printf("Price: %.2lf\n", book.price);
	printf("Category: %s\n", category[book.category]);
	printf(" \n");
}

void initBook(BOOK& book) { //добавить книгу
	const int len_author = 50;
	const int len_title = 100;

	printf("Enter author of the book: ");
	scanf_s(" %49[^\n]", book.author, len_author); 
	while (getchar() != '\n'); 

	printf("Enter title of the book: ");
	scanf_s(" %99[^\n]", book.title, len_title);
	while (getchar() != '\n');

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
				printf("Error! Too small or too big year of publishing. Try again:");
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
			if (price_n < 0) {
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
	printf("Enter category of the book: (1 - Classic, 2 - Science Fiction, 3 - Fairy Tale, 4 - Short Stories, 5 - Educational Literature): ");
	while (true) {
		if (scanf_s("%d", &categor_n) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			if (categor_n >= 0 && categor_n < 6) {
				book.category = categor_n;
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