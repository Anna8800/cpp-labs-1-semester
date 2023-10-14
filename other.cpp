using namespace std;
#include "other.h"
#include <limits.h>
#include <cstdlib>
#include <cstdarg>
#include <string.h>
#include <iostream>

int number = 15; // значение для задания 1
int& ref = number; //инициализируем ссылку
///////////////////////////////////////////////////
//task 2
int IncByValue(int val) {
	return ++val;
}
void IncByPointer(int* val) {
	++(*val);
}
void IncByReference(int& val) {
	++val;
}

//task 2a
void swap(int* X, int* Y) {
	int tmp = *X;
	*X = *Y;
	*Y = tmp;
}
void swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

//task 3a
int findMin(int ar[][M], int row) {
	int Min = INT_MAX;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < M; j++) {
			if (ar[i][j] < Min) { Min = ar[i][j]; }
		}
	}
	return Min;
}
int findMin(int** p, int rows, int cols) {
	int Min = INT_MAX;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (p[i][j] < Min) { Min = p[i][j]; }
		}
	}
	return Min;
}

//task 3b
char MyStrCmp(const char* a, const char* b) {
	int res;
	if (strcmp(a, b) > 0) { res = 1; }
	else if (strcmp(a, b) == 0) {res = 0;}
	else { res = -1; }
	return res;
}

//task 4
int DayOfYear(int day, int month, int year, int ar[][12]) {
	int num=0;
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {
		for (int i = 0; i < month-1; i++) {
			num += ar[1][i];
		}
		num += day;
	}
	else {
		for (int i = 0; i < month-1; i++) {
			num += ar[0][i];
		}
		num += day;
	}
	return num;
}
void DayOfMonth(int day_of_year, int month, int year, int (&ar)[2][12], int* res_day, int* res_month) {
	int day_month = day_of_year;
	int num_month = month;
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {
		while (day_month > 31) {
			day_month -= ar[1][num_month];
			num_month++;
		}
	}
	else {
		while (day_month > 31) {
			day_month -= ar[0][num_month];
			num_month++;
		}
	}
	*res_day = day_month;
	*res_month = num_month + 1;
}

//task 5
void Unique_Value(int *& ar, int & size, int new_element) { //int *& ar - указатель на целочисленный массив
	for (int i = 0; i < size; i++) {
		if (ar[i] == new_element) { return; } //если значение существует, ничего не делаем
	}
	//если значение уникально - выполняем код дальше, нет - выходим из функции
	int newsize = size + 1;
	int* new_arr = new int [newsize]; //создаем новый массив, который больше на один элемент
	for (int i = 0; i < size; i++) {
		new_arr[i] = ar[i]; //переносим значения из старого массива в новый
	}
	new_arr[size] = new_element; //добавляем новый уникальный элемент
	delete[] ar;
	ar = new_arr; //переключаем указатель на новый массив
	size++;
}
void Print_arr(const int ar[], int size) {
	for (int i = 0; i < size; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}

//task 6
int Recursive_f(int n) {
	if (n <= 1) return 1;
	else {
		return n + Recursive_f(n - 1);
	}
}

//Подсказка-заготовка для задания 7а
//Без использования макросов
void VarArgs(int arg1, ...){
	int number = 0;	//счетчик элементов
	//Объявите указатель на int и инициализируйте его адресом первого аргумента
	int* p = &arg1;
	//Пока не достигнут конец списка
	cout << "elements: " << " ";
	while (*p != 0) {
		// а) печать значения очередного аргумента
		cout << *p << " ";
		// б) модификация указателя (он должен указывать на следующий аргумент списка)
		p++;
		// в) увеличить счетчик элементов
		number++;
	}
	cout << endl;
	//Печать числа элементов
	cout << "number of elements: " << number << endl;
}
//task 7b
void VarArgsMacros(int arg1, ...) {
	int number = 0;
	int i = arg1; //значение обязательного параметра
	va_list p; //универсальный указатель
	cout << "elements: " << " ";
	va_start (p, arg1);
	while (i != 0) {
		number++;
		cout << i << " ";
		i = va_arg(p, int);
	}
	cout << endl;
	cout << "number of elements: " << number << endl;
	va_end(p);
}
//task 8
int* MyMin(int arr[], int len) {
	int* p = arr;
	for (int i = 0; i < len; i++) {
		if (arr[i] < *p) {
			p = &arr[i];
		}
	}
	return p;
}


