#include "book.h"
using namespace std;
#include <iostream>

const char* category[] = {
	"Classic",
	"Science fiction",
	"Fairy tale",
	"Short stories"
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
	printf("Enter category of the book: (1 - Classic, 2 - Science Fiction, 3 - Fairy Tale, 4 - Short Stories): ");
	while (true) {
		if (scanf_s("%d", &categor_n) != 1) { // проверяем успешность считывания значения
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
			continue;
		}
		else {
			if (categor_n >= 0 && categor_n < 5) {
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

/*

//task 2a
void Sort(char* pcFirst, int nNumber, int size,
	void (*Swap)(void*, void*), int (*Compare)(void*, void*))
{
	int i;
	for (i = 1; i < nNumber; i++)
		for (int j = nNumber - 1; j >= i; j--)
		{
			char* pCurrent = pcFirst + j * size;
			char* pPrevious = pcFirst + (j - 1) * size;
			if ((*Compare)(pPrevious, pCurrent) > 0) //требуется переставить
				(*Swap)(pPrevious, pCurrent);
		}
}
void SwapInt(void* p1, void* p2)
{
	int* x = static_cast<int*>(p1);
	int* y = static_cast<int*>(p2);
	int temp = *x;
	*x = *y;
	*y = temp;
}
int CmpInt(void* p1, void* p2)
{
	int nResult;
	int* px = static_cast<int*>(p1); //преобразуем из void* указателей в указатели на int
	int* py = static_cast<int*>(p2);
	nResult = *px - *py; //сравниваем значения, на которые указывают указатели
	// тк числа целые, то результат сравнения будет сразу в нужном формате (>0, <0, =0)
	return nResult;
}
void Print_arr(const int ar[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}
//task 2b
void Print_arr(const double ar[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}
void SwapDouble(void* p1, void* p2) {
	double* x = static_cast<double*>(p1);
	double* y = static_cast<double*>(p2);
	double temp = *x;
	*x = *y;
	*y = temp;
}
int CmpDouble(void* p1, void* p2) {
	int nResult;
	double* px = static_cast<double*>(p1); //преобразуем из void* указателей в указатели на double
	double* py = static_cast<double*>(p2);
	if (*px - *py > 0) { nResult = 1; } //сравниваем значения, на которые указывают указатели
	else if (*px - *py < 0) { nResult = -1; }
	else { nResult = 0; }
	return nResult;
}
//task 2c
void SwapStr(void* p1, void* p2) {
	char** x = static_cast<char**>(p1);
	char** y = static_cast<char**>(p2);
	char* temp = *x;
	*x = *y;
	*y = temp;
}
int CmpStr(void* p1, void* p2) {
	//int nResult;
	char** px = static_cast<char**>(p1);
	char** py = static_cast<char**>(p2);
	return strcmp(*px, *py);
}
void Print_arr(const char* arr[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
//task 3
const char* GetString1() {
	return "Mordor, Gandalf, is it left or right?\n";
}
const char* GetString2() {
	return "My precious...\n";
}
const char* GetString3() {
	return "They're taking the hobbits to Isengard!\n";
}
const char* GetString4() {
	return "A wizard is never late.\n";
}
const char* GetString5() {
	return "All we have to decide is what to do with the time that is given to us.\n";
}
//task 3
char* Cut_off_string(const char* origin, int length, char* slice) {
	if (strlen(origin) > (length - 1)) {
		printf("Error: too many symbols! \n");
		strncpy_s(slice, length, origin, length - 1);
		slice[length - 1] = '\0';
	}
	else { strcpy_s(slice, length, origin); }

	return slice;
}
}
*/