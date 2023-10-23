#include "lab5_other.h"
using namespace std;
#include <iostream>
///////////////////////////////////////////////////

//task 1
double Sum(double a1, double a2) {
	return (a1 + a2);
}
double Sub(double a1, double a2) {
	return (a1 - a2);
}
double Mul(double a1, double a2) {
	return (a1 * a2);
}
double Div(double a1, double a2) {
	return (a1 / a2);
}
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
	char *temp = *x;
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
	else {strcpy_s(slice, length, origin);}

	return slice;
}
 //task 4
const char* categor_str(Category category) { //для приведения категории к строке
	switch (category) {
	case Category::CLASSIC:
		return "Classic";
	case Category::SCIENCE_FICTION:
		return "Science Fiction";
	case Category::FAIRY_TALE:
		return "Fairy Tale";
	case Category::SHORT_STORIES:
		return "Short Stories";
	default: 
		return "help me";
	}
}
void Print_book(const BOOK &book) {
	printf("Author: %s\n", book.author);
	printf("Title: %s\n", book.title);
	printf("Year: %hd\n", book.year);
	printf("Price: %d\n", book.price);
	const char* categ = categor_str(book.category);
	printf("Category: %s\n", categ);
	printf(" \n");
}
 //task 5
void Fill_struct(BOOK& book) {
	const int len_author = 50;
	const int len_title = 100;
	
	printf("Enter author of the book: ");
	scanf_s(" %49[^\n]", book.author, len_author); //ограничиваем число символов, которые могут быть прочитаны
	while (getchar() != '\n'); //очистка буфера

	printf("Enter title of the book: ");
	scanf_s(" %99[^\n]", book.title, len_title);
	while (getchar() != '\n');

	short year_n;
	printf("Enter year of publishing: ");
	while (true){
		scanf_s("%hd", &year_n);
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

	int price_n;
	printf("Enter price of the book: ");
	while (true) {
		scanf_s("%d", &price_n);
		if (price_n<0) {
			printf("Error! Too small price. Try again:");
			while (getchar() != '\n');
			continue;
		}
		else {
			book.price = price_n;
			break;
		}
	}

	int categor_n;
	printf("Enter category of the book: (1 - Classic, 2 - Science Fiction, 3 - Fairy Tale, 4 - Short Stories): ");
	while (true){
		scanf_s("%d", &categor_n);
		if (categor_n >= 0 && categor_n < 5) {
			book.category = static_cast<Category>(categor_n - 1);
			break;
		}
		else {
			printf("Wrong value of category! Try again: ");
			while (getchar() != '\n');
			continue;
		}
	}
}