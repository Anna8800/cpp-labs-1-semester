﻿/*************************************************************
	Практическое занятие №5. Структуры
//динамический массив структур
//поиск
//сортировка
//сохранение в файле
//чтение из файла
*************************************************************/
#include "support.h"
#include "book_collection.h"
#include "book.h" 
#include "sort.h"
#include <stdio.h> 
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vld.h>
#define	  stop __asm nop	




void main()
{
	//Используйте структуру BOOK, созданную в предыдущей работе.
	//Для этого достаточно переписать и подключить к проекту файлы
	//book.h и book.cpp

	//Задание 1. Создаем «картотеку».
	//«Картотека» - это массив структур => нужно такой массив создать.
	//Замечание: размер массива придется увеличивать по мере добавления книг =>
	//Каким должен быть такой массив? >> динамический


	//Пользователь должен иметь возможность по своему желанию выполнять
	//разные действия с картотекой => нужно такую возможность ему
	//предоставить: это может выглядеть как вывод "меню" (перечень
	//возможных действий и соответствующих реакций пользователя), например:
	//Распечатать содержимое картотеки (1)
	//Ввести новую книгу (2) 
	//Удалить существующую(ие) (3)
	//Записать текущее содержимое картотеки в файл (4)
	//Считать из файла содержимое в картотеку (5)
	//...
	//Выход из программы (...)


	//Реализуйте посредством функций разные возможности работы с картотекой


	//Подсказка1: для файлового ввода/вывода используйте функции fprintf и fscanf
	//(заголовочный файл <cstdio>

	// Подсказка2: удобно в качестве первого данного в файле хранить количество
	// книг в картотеке
	//Если файл существует и его удалось открыть
	//if()
	//{
	//Чтение данных из файла
	//а) считали количество элементов
	//б) создали массив требуемой размерности
	//в) считали данные из файла в массив
	//}


	const char* filename = "recent.txt";
	print_recent(filename);
	Library library;
	createLibrary(library);
	const char names[256] = "";
	enterName((char*)names);
	recent_files(names, filename);
	char choice = 0;
	init_readme();
	bool run = true;
	while (run) {
		scanf_s(" %c", &choice, 1); 
		(void)getchar();
		switch (choice) {
		case 'h':
			init_readme();
			break;
		case 'l':
			loadLibrary(&library, names);
			break;
		case 'p':
			printLibrary(library);
			break;
		case 't':
			printTitles(library);
			break;
		case 'a':
			addBook(library);
			break;
		case 'd':
			deleteBook(library);
			break;
		case 'q':
			printf("Stopping the program...\n");
			run = false;
			break;
		case 's':
			scanLibrary(&library, names);
			break;
		case 'b':
			countBookCategory(&library, names);
			break;
		
		

		//****************************************************************
		//Задание 2. Предоставьте пользователю возможность выводить перечень книг
		//в определенном порядке => напишите функцию (функции) сортировки массива
		//по любому из полей структуры.
		//Замечание: признак - "по какому полю сортируем" можно ввести с помощью
		//перечисления.
		case 'r':
			choise_field_to_sort(library);
			break;
		default:
			printf("Invalid letter! If you need a help, press [h]. Try again: \n");
			break;
		}
	}
	clearLibrary(library);
}