﻿#include "lab5_other.h"
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