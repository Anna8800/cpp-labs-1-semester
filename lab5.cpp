
/*************************************************************
	Практическое занятие №5.
	"Старые" потоковые функции стандартной библиотеки
	Указатели на функции
	Структуры
*************************************************************/
#include <tchar.h>
#include <iostream>
#include <cstdio>
#include "lab5_other.h"
#include <cmath>
#include <vld.h>


#define	  stop __asm nop

int _tmain()
{
	//I Тема "Старые" потоковые функции стандартной библиотеки
	//Задание 1. С помощью функции scanf_s сформируйте три коэффициента: A,B,C
	printf("task 1\n");
	double A, B, C;
	printf("Enter A: ");
	scanf_s("%lf", &A);
	printf("Enter B: ");
	scanf_s("%lf", &B);
	printf("Enter C: ");
	scanf_s("%lf", &C);
	printf("a=%lf, b=%lf, c=%lf\n", A, B, C);

	//Задание 2. Выведите (красиво!) таблицу значений y=A*x*x + B*x + C
	//при изменении x в диапазоне -2 до +2 с шагом 0.5
	printf("task 2\n");
	printf("|   x  |   f(x) |\n");
	printf("|---------------|\n");
	for (double x = -2; x < 2.01; x += 0.5) {
		printf("|%6.1lf|  %6.2lf|\n", x, (A*x*x+B*x+C)); 
		//формируем поле шириной шесть символов + 1 цифра после запятой
	}

///////////////////////////////////////////////////////////////////
	//II Тема Указатели на функции
	{
		printf("task 1\n");
		//Задание 1. Указатель на функцию. "Калькулятор".
		//Напишите функции:
		//1)Sum - принимает два значения double и возвращает сумму этих значений
		//2)Sub- принимает два значения double и возвращает разность этих значений
		//3)Mul - *
		//4)Div - /
		//5)а для возведения в степень можете использовать функцию стандартной библиотеки
		//		- pow(). Подсказка 1: прототип функции находится в <cmath>.
		//		Подсказка 2: стандартная библиотека предоставляет несколько перегруженных
		//		вариантов этой функции, а Вам потребуется сформировать указатель на 
		//		double pow(double, double);

		//Предоставьте пользователю	следующую возможность:
		//пока пользователь хочет пользоваться услугами Вашего калькулятора,
		//он может вводить два значения и знак операции
		//а Вы выводите результат. Результат получаете посредством вызова
		//соответствующей Вашей функции по указателю.
		//Предусмотрите возможность ввода непредусмотренного знака операции

		bool continueCalc = true;
		char choice = 0;
		char operat = 0;
		double x, y;
		while (continueCalc) {
			double (*func) (double, double) = nullptr;
			printf("Enter your task: ");
			scanf_s("%lf  %c %lf", &x, &operat, 1, &y); //предовтращение переполнения буфера - ждем одно значение, получаем одно значение
			switch (operat) {
			case '+':
				func = Sum;
				break;
			case '-':
				func = Sub;
				break;
			case '*':
				func = Mul;
				break;
			case '/':
				func = Div;
				break;
			case '^':
				func = pow;
				break;
			default:
				break;
			}
			if (func) {
				printf("x %c y = %f\n", operat, func(x, y));
			}
			else { printf("Error: undefined operator!\n"); }
			//проверка на следующую итерацию 
			printf("Do you want to use the calculator? y/n  ");
			scanf_s(" %c", &choice, 1);
			switch (choice) {
				case 'y':
				case 'Y': 
					break;
				case 'n':
				case 'N':
					continueCalc = false;
					break;
				default:
					printf("Error: incorrect value!");
					continueCalc = false;
  			}
		
		}
		stop
	}
	{
		//Задание 2. Указатель на функцию в качестве аргумента.
		//Дана заготовка функции сортировки любых объектов - Sort.
		//Функция принимает следующие параметры:
		//1) указатель на первый сортируемый элемент
		//2) количество сортируемых элементов
		//3) размер элемента в байтах
		//4) указатель на функцию перестановки элементов
		//5) указатель на функцию сравнения элементов
		
		//2a. Напишите функцию перестановки двух целых значений -
		// SwapInt, которая принимает два void указателя и 
		//меняет значения местами

		//Напишите функцию сравнения двух целых значений -
		// CmpInt, которая принимает два void указателя и
		//возвращает int результат сравнения: 
		//<0 - первый элемент меньше, чем второй
		//=0 - равны
		//>0 - первый элемент больше, чем второй

		printf("task 2a\n");
		srand(static_cast<int>(time(0)));
		const int N = 10;
		int nAr[N]; //массив для сортировки
		for (int i = 0; i < N; i++) {
			nAr[i] = rand() % 50;
		}
		//Печать исходного массива
		Print_arr(nAr, N);
		//Вызов сортировки
		int nTotal = N;			//количество элементов в массиве
		Sort(reinterpret_cast<char*>(&nAr[0]), nTotal, sizeof(int), SwapInt, CmpInt);
		//Печать результатов сортировки
		Print_arr(nAr, N);

		stop
	
	
		//Задание 2б. По аналогии с 2а создайте вспомогательные
		//функции - SwapDouble и CmpDouble и вызовите функцию Sort
		//для сортировки массива вещественных значений.

		printf("task 2b\n");
		srand(static_cast<int>(time(0)));
		double dAr[N]; 
		for (int i = 0; i < N; i++) {
			dAr[i] = rand() % 500 /10.05;
		}
		Print_arr(dAr, N);
		int dTotal = N;
		Sort(reinterpret_cast<char*>(&dAr[0]), dTotal, sizeof(double), SwapDouble, CmpDouble);
		Print_arr(dAr, N);
	
	
		//Задание 2в*. По аналогии с 2а создайте вспомогательные
		//функции - SwapStr и CmpStr и вызовите функцию Sort
		//для сортировки массива указателей на строки.
		printf("task 2c\n");
		const char* arStr[] = { "Python", "C++", "JavaScript", "C", "PHP", "HTML", "Go", "Ruby", "Pascal"};
		int size_of_arr = sizeof(arStr) / sizeof(arStr[0]);
		Print_arr(arStr, size_of_arr);
		int sTotal = size_of_arr;
		Sort(reinterpret_cast<char*>(&arStr[0]), sTotal, sizeof(char*), SwapStr, CmpStr);
		Print_arr(arStr, size_of_arr);

	}
	{
		//Задание 3. Массивы указателей на функцию.
		//Напишите несколько функций вида
		//const char* GetString1();
		//const char* GetString2();
		//		...., каждая из функций возвращает указатель на свою строку
		//(подумайте - какой адрес Вы имеете право возвращать из функции)

		//Объявите и проинициализируйте массив указателей на функции
		//GetString1,GetString2...
		printf("task 3\n");
		//массив указателей на функции, которые возвращают указатели на строки
		const char* (* Arr_of_str[])() = { GetString1, GetString2, GetString3, GetString4, GetString5 };

		//Введите номер функции, которую Вы хотите вызвать:
		int n;
		printf("Enter number of function (1 to 5): ");
		scanf_s("%d", &n);

		//Вызовите функцию и распечатайте результат
		if (n < 6 and n > 0) {
			printf(Arr_of_str[n-1]());
		}
		else { printf("Incorrect number of function!\n"); }

	}
	//////////////////////////////////////////////////////////////////////////////////////

		//III Тема. Структуры С.	
	printf("Item III. Structures.\n");
	{
		//Задание 1. Объявите структуру BOOK, описывающую книгу
		//(автор, заглавие, год издания, цена, категория…).
		//Подумайте: какого типа могут быть поля структуры.
		//Подсказка: объявление структуры рекомендуется выносить
		//в заголовочный файл.

	
		//Задание 2. Создайте разными способами (глобальный, локальный, статический,
		//динамический) экземпляры (объекты) типа BOOK (без инициализации).
		//Определите - сколько памяти отводит компилятор под каждый
		//такой объект. Как инициализируются (или не инициализируются) поля
		//структуры. Подумайте: от чего зависит объем выделяемой памяти?
		printf("task 2\n");

		BOOK globalBook; //глобальный экземпляр
		printf("global size = ");
		printf("% zu\n", sizeof(globalBook));
		BOOK localBook;  //локальный экземпляр
		printf("local size = ");
		printf("%zu\n", sizeof(localBook));
		BOOK staticBook; //статический экземпляр
		printf("static size = ");
		printf("%zu\n", sizeof(staticBook));
		// для глобального, статического, локального экземпляров объем выделяемой памяти = 160 байт
		// char author[50] = 50 байт
		// char title[100] = 100 байт
		// short year = 2 байта
		// int price = 4 байта
		// Category category = 4 байта

		BOOK* dynamicBook = new BOOK; //динамический экземпляр
		printf("dynamic size = ");
		printf("%zu\n", sizeof(dynamicBook));
		// dynamicBook - указатель на объект типа BOOK, занимает 4 байта
		// сам объект, на который указывает указатель будет занимать 160+4 байта


		//Задание 3. Заполните поля созданных объектов.
		//Замечание: если для хранения строки используется массив, необходимо
		//предусмотреть "защиту" от выхода за границы массива.
		printf("task 3\n");

		const int len_author = 50;
		const int len_title = 100;
		char* slice_au = new char[len_author];
		char* slice_t = new char[len_title];

		const char author_g[] = "S. King111111111111111111111111111111111111111111111111111111111111111111111111";
		const char title_g[] = "The Dark Tower";
		slice_au = Cut_off_string(author_g, len_author, slice_au); //функция, реализующая защиту от переполнения массива
		strcpy_s(globalBook.author, slice_au);
		slice_t = Cut_off_string(title_g, len_title, slice_t); 
		strcpy_s(globalBook.title, slice_t);
		globalBook.year = 2004;
		globalBook.price = 1500;
		globalBook.category = Category::SCIENCE_FICTION;
	
		const char author_l[] = "F. M. Dostoevsky";
		const char title_l[] = "Crime and Punishment";
		slice_au = Cut_off_string(author_l, len_author, slice_au);
		strcpy_s(localBook.author, slice_au);
		slice_t = Cut_off_string(title_l, len_title, slice_t);
		strcpy_s(localBook.title, slice_t);
		localBook.year = 1866;
		localBook.price = 1000;
		localBook.category = Category::CLASSIC;

		const char author_s[] = "K. Chukovsky";
		const char title_s[] = "Buzzy-Wuzzy Busy Fly";
		slice_au = Cut_off_string(author_s, len_author, slice_au); //функция, реализующая защиту от переполнения массива
		strcpy_s(staticBook.author, slice_au);
		slice_t = Cut_off_string(title_s, len_title, slice_t);
		strcpy_s(staticBook.title, slice_t);
		staticBook.year = 1923;
		staticBook.price = 600;
		staticBook.category = Category::FAIRY_TALE;

		const char author_d[] = "R. Bradbury";
		const char title_d[] = "The Screaming Woman";
		slice_au = Cut_off_string(author_d, len_author, slice_au); //функция, реализующая защиту от переполнения массива
		strcpy_s(dynamicBook->author, slice_au);
		slice_t = Cut_off_string(title_d, len_title, slice_t);
		strcpy_s(dynamicBook->title, slice_t);
		dynamicBook->year = 1955;
		dynamicBook->price = 900;
		dynamicBook->category = Category::SHORT_STORIES;

		//Задание 4. Напишите функцию, выводящую на экран реквизиты книги.
		//Подумайте: как эффективнее передавать экземпляр BOOK в функцию.
		//Для вывода на консоль используйте функцию стандартной библиотеки printf
		printf("task 4\n");
		//эффективнее всего передавать значения по константной ссылке - 
		//функция получает доступ к объекту без создания его копий

		Print_book(globalBook);
		Print_book(localBook);
		Print_book(staticBook);
		Print_book(*dynamicBook);

	
		//Задание 5. Напишите функцию для формирования полей структуры.
		//Для ввода используйте функцию стандартной библиотеки scanf
		//Замечание: неплохо заложить в такую функцию возможность проверки
		//корректности введенного значения, например, год издания не может быть
		//меньше, чем... (год появления письменности), категорию пользователь
		//должен выбирать из существующих, цена не может быть отрицательной...
		printf("task 5\n");

		BOOK newBook;
		Fill_struct(newBook);
		Print_book(newBook);

		delete[] slice_au;
		delete[] slice_t;
		delete dynamicBook;
	}
	
	return 0;
}//main
