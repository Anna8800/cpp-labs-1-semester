﻿/*************************************************************
	Практическое занятие №3. Встроенные массивы.
							Динамическое выделение памяти.
							Простейшие алгоритмы сортировки и поиска.
							Сложные указатели.
							Ссылки.
*************************************************************/

#include <iostream>
using namespace std;
#define	  stop __asm 
#include <vld.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>


int main()
{
	///////////////////////////////////////////////////////////////
	//			Встроенные массивы                               //
	///////////////////////////////////////////////////////////////

		//Задание 1. Объявите трехмерный N*M*K массив и сформируйте указанные
		//значения элементов следующим образом:
		//а) проинициализируйте массив при объявлении
	const int N = 3, M = 3, K = 3;
	int inic_ar1[N][M][K] = {
		{ {11, 12, 13} , {14, 15, 16} , {17, 18, 19}},
		{ {21, 22, 23} , {24, 25, 26} , {27, 28, 29}},
		{ {31, 32, 33} , {34, 35, 36} , {37, 38, 39}}

	};
	//б)* объявите неинициализированный массив и присвойте значения элементам
	//	с помощью кода
	//					 |--------|
	//				   / |3  3  3 |
	//    			 |---------|3 |
	//			   / | 2  2  2 |3 |
	//			  |---------|2 |__|
	//			  | 1  1  1 |2 | /
	//			  | 1  1  1 |__|
	//			  | 1  1  1 | /
	//			  |_________|
	//Средствами отладчика проверьте правильность Вашего решения.
	int notinic_ar1[N][M][K];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < K; k++)
			{
				notinic_ar1[i][j][k] = i + 1;
			}
		}
	}
	//в) найдите сумму элементов массива
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < K; k++)
			{
				sum += notinic_ar1[i][j][k];
			}
		}
	}
	std::cout << "task 1.B" << std::endl;
	std::cout << sum << std::endl;
	//г) проинициализируйте массив при определении:
	//					 |--------|
	//				   / |3  0  0 |
	//    			 |---------|0 |
	//			   / | 2  0  0 |0 |
	//			  |---------|0 |__|
	//			  | 1  0  0 |0 | /
	//			  | 0  0  0 |__|
	//			  | 0  0  0 | /
	//			  |_________|
	int null_arr[N][M][K] = { {1}, {2}, {3} };

	//д)* Инициализация массивов строковыми литералами:
	//Объявите и проинициализируйте строковыми литералами два массива:
	//двухмерный массив и массив указателей. Поясните разницу в использовании
	//элементов таких массивов.
	char arr_ch[][6] = { "Hey", "Hello", "Ciao", "Hej" };
	// двухмерный массив
	// хранит значения строкового литерала
	arr_ch[1][1] = 'B'; //вместо "Hello" "HBllo", т.е. можно менять элементы литерала
	const char* arr_p[] = { "Hey", "Hello", "Ciao", "Hej" };
	// массив указателей
	// хранит адреса строк начала строкового литерала
	//arr_p[1][1] = 'B' //нельзя модифицировать константную переменную



		///////////////////////////////////////////////////////////////
		//			Динамическое выделение памяти                    //
		///////////////////////////////////////////////////////////////
			//Задание2. Создайте динамический двухмерный массив с размерностями,
			//вычисляемыми в процессе выполнения программы - N*M.
			//Задайте значения элементов помощью генератора случайных чисел.
			//Найдите  сумму элементов.
			//Подсказка 1: для генерации случайных чисел используйте функцию
			//стандартной библиотеки - rand() (<cstdlib>)
			//Подсказка 2: На самом деле те значения, которые создаются генератором случайных
			//чисел являются «псевдослучайными», то есть при двух последовательных запусках
			//приложения Вы получаете две одинаковые последовательности значений.
			//Для того чтобы генерируемые "случайные" значения были разными при каждом 
			//запуске приложения используйте функции стандартной библиотеки srand() (<cstdlib>)
			//и time() (<ctime>).
			//Функция srand() осуществляет «привязку» начала генерации к указанному в качестве параметра значению.
			//Функция time() задает эту точку отсчета, считывая текущее время
	{
		cout << "task 2" << endl;
		int N, M;
		int sum_rand_ar = 0;
		srand(static_cast<int>(time(0)));
		N = rand() % 10; //ограничим рандомные числа до 10, чтобы не получить слишком большую матрицу
		M = rand() % 10;
		cout << N << " " << M << endl;
		int* p = new int[N * M];
		int** pp = new int* [N];
		for (int i = 0; i < N; i++)
		{
			pp[i] = p + i * M;
			for (int j = 0; j < M; j++)
			{
				pp[i][j] = rand() % 100;
				sum_rand_ar += pp[i][j];
			}
		}
		cout << "Unsorted arr" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cout << pp[i][j] << " ";
			}
			cout << endl;
		}
		cout << "sum_rand_ar = " << sum_rand_ar << endl;

		//Задание2а. В сформированном массиве отсортируйте каждую строку по
		//убыванию значений. Используйте сортировку "выбором"
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int max_J = j; //индекс максимального элемента в строке
				for (int y = j + 1; y < M; y++) //проверка оставшихся элементов строки
				{
					if (pp[i][y] > pp[i][max_J]) max_J = y;
				}
				int tmp = pp[i][max_J]; //замена значений
				pp[i][max_J] = pp[i][j];
				pp[i][j] = tmp;
			}
		}

		cout << "Sorted arr" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cout << pp[i][j] << " ";
			}
			cout << endl;
		}
		delete[]p;
		delete[]pp;
		p = 0;
		pp = 0;
	}

	//Задание2б. Объявите одномерный массив размерностью N.
	//Сформируйте значение i-ого элемента одномерного массива  
	//равным среднему значению элементов i-ой строки
	//двухмерного массива
	{
		cout << "task 2b" << endl;
		const int N = 3;
		const int M = 4;
		int ar_two[N][M] = { {1, 2, 3, 45} , {11, 12, 13, 14} , {21, 22, 23, 24} };
		float arr_sr_arifm[N]; //искомый массив
		for (int i = 0; i < N; i++) {
			float sum_strok = 0;
			for (int j = 0; j < M; j++) {
				sum_strok += ar_two[i][j];
			}
			float k = sum_strok / M;
			arr_sr_arifm[i] = k;
		}
		for (int i = 0; i < N; i++) {  //вывод одномерного массива
			cout << arr_sr_arifm[i] << " ";
		}
		cout << endl;
	}

	//Подсказка - не забудьте освободить память!





	/////////////////////////////////////////////////////////////////////
	//Задание 3. а) Напишите фрагмент кода, который вводит X целых чисел с помощью
	//потока ввода в объявленный Вами встроенный одномерный массив, каждый раз
	//упорядочивая полученное значение по возрастанию

	{
		cout << "task 3.1" << endl;
		const int X = 5;
		int arr_sorted[X];
		cout << "enter number" << endl;
		for (int i = 0; i < X; i++)
		{
			cin >> arr_sorted[i];
			int j = i;
			while (j > 0 and arr_sorted[j] < arr_sorted[j - 1])
			{
				int tmp = arr_sorted[j];
				arr_sorted[j] = arr_sorted[j - 1];
				arr_sorted[j - 1] = tmp;
				j--;
			}
		}
		//std::sort(arr_sorted, arr_sorted + i + 1);
		for (int i = 0; i < X; i++) {  //вывод одномерного массива
			cout << arr_sorted[i] << " ";
		}
		cout << endl;
	}



	//б) Простой поиск.
	//Модифицируйте предыдущее задание следующим образом:очередное значение
	//вводится в массив только при условии, что там еще такого нет (то есть 
	//дубли игнорируются
	{
		cout << "task 3.2" << endl;
		const int N = 5;
		int count = N;
		int new_element; //вводимое значение, которое мы будем проверять на уникальность
		int arr2_sorted[N];
		cout << "enter unic number" << endl;
		while (count)
		{
			bool unic_flag = true;
			cin >> new_element;
			for (int i = 0; i < N; i++) {
				if (arr2_sorted[i] == new_element) unic_flag = false;
			}
			if (unic_flag == true) {
				count--;
				arr2_sorted[count] = new_element;
				for (int i = 0; i < N; i++)
				{
					while (i > 0 and arr2_sorted[i] < arr2_sorted[i - 1])
					{
						int tmp = arr2_sorted[i];
						arr2_sorted[i] = arr2_sorted[i - 1];
						arr2_sorted[i - 1] = tmp;
						i--;
					}
				}
			}
		}
		for (int i = 0; i < N; i++) {  //вывод одномерного массива
			cout << arr2_sorted[i] << " ";
		}
		cout << endl;
	}


	///////////////////////////////////////////////////////////////////////////
	//Задание 4*.С помощью данной заготовки напишите программу,
	//которая:
	//вводит строки с клавиатуры с помощью cin>>...
	//в объявленный Вами двухмерный встроенный массив 5*80 элементов типа char;
	//признаком конца ввода является символ * (то есть строка - "*") или
	//заполнение массива (больше свободных строк нет);
	//сортировка строк в алфавитном порядке. Пояснение: крайне
	//не рекомендуется для сортировки сложных объектов физически
	//перемещать их в памяти. Намного эффективнее завести массив
	//указателей на соответствующие строки и перемещать только
	//указатели.

	//Подсказка: для лексиграфического сравнения строк пользуйтесь
	//функцией стандартной библиотеки strcmp(...), заголовочный файл <string>.
	{
		cout << "task 4" << endl;
		//Определите необходимые значения как константы
#define STOP_STRING "*"	//признак "прекратить ввод"
		const int M = 80;	//максимальный размер одной строки
		const int N = 5;	//максимальное количество строк в массиве

		//Объявите двухмерный массив с именем cBuffer типа char и размерностью N*M
		char cBuffer[N][M];
		char stroka[M] = {};
		//Объявите массив (с именем cPointers) указателей на строки размерностью N
		char* cPointers[N];

		//Цикл ввода строк:
		//а) выведите приглашение для ввода
		cout << "Enter line" << endl;
		//б) пока не введена строка STOP_STRING или не заполнен весь массив
		int i = 0;
		int readen = 0;
		while (i < N) {
			cin >> stroka;
			if (strcmp(stroka, STOP_STRING) == 0) break; //если введена строка - признак окончания, то выйти из цикла
			if (strlen(stroka) > (M - 1)) break; //если длина строки больше установленной
			strcpy_s(cBuffer[i], stroka); //ввод строки в массив cBuffer:
			i++;
			readen++; //"хорошие" значения
		}
		//Присвойте элементу массива cPointers с индексом nIndex
		//указатель на строку с номером nIndex в массиве cBuffer
		for (int nIndex = 0; nIndex < readen; nIndex++) {
			cPointers[nIndex] = cBuffer[nIndex];
		}

		//Выдать диагностику о том, что прием строк завершен.
		cout << "All lines entered" << endl;

		//Теперь сортируем строки:
		//Цикл сортировки строк по методу "всплывающего пузырька" в
		//порядке возрастания. На каждой итерации - промежуточная печать
		//отсортированных строк
		for (int i = readen; i > 0; i--) {
			for (int j = readen - 1; j > 0; j--) {
				if (strcmp(cPointers[j], cPointers[j - 1]) < 0) {
					char* tmp = cPointers[j];
					cPointers[j] = cPointers[j - 1];
					cPointers[j - 1] = tmp;
				}
			}
			for (int k = 0; k < readen; k++) { cout << cPointers[k] << " "; }
			cout << endl;
		}
	}


	//Задание 5*. Реализуйте задание №4, используя не встроенные,
	//а динамические массивы (массив?). Так как строки могут быть разной длины,
	//эффективным решением было бы отводить под каждую строку ровно столько байтов,
	//сколько требуется для ее хранения.
	//При этом необходимые параметры (количество строк) сформируйте с помощью потока ввода
	{

		cout << "task 5" << endl;
		const int MK = 80;
		int nStringNumber;
		char value_strok[MK] = {};
		int readenD = 0;
		cin >> nStringNumber;
		cout << "enter line" << endl;
		char** p_Buffer = new char* [nStringNumber];

		//Цикл ввода строк:
		for (int i = 0; i < nStringNumber; i++) {
			cin >> value_strok;
			if (strcmp(value_strok, STOP_STRING) == 0) break;
			if (strlen(value_strok) > (MK - 1)) break;
			int memory = strlen(value_strok); //память, необходимая для текущей строки
			p_Buffer[i] = new char[memory + 1];
			for (int j = 0; j < memory; j++) {
				p_Buffer[i][j] = value_strok[j];
			}
			p_Buffer[i][memory] = '\0'; //здесь конец строки
			readenD++;
			}
		//Цикл сортировки строк по методу "всплывающего пузырька" в
		//порядке возрастания кода первого символа
		for (int i = readenD; i > 0; i--) {
			for (int j = readenD - 1; j > 0; j--) {
				if (strcmp(p_Buffer[j], p_Buffer[j - 1]) < 0) {
					char* temp = p_Buffer[j];
					p_Buffer[j] = p_Buffer[j - 1];
					p_Buffer[j - 1] = temp;
				}
			}
		}
		//печать отсортированных строк
		for (int k = 0; k < readenD; k++) { cout << p_Buffer[k] << " "; }
		cout << endl;
		//Освобождение занятой памяти:
		for (int i = 0; i < readenD; i++) {
			delete[] p_Buffer[i];
		}
		delete[] p_Buffer;
		p_Buffer = 0;
	}



	//Задание 6*. Объявление и использование указателей на многомерные
	// массивы. Проинициализируйте трехмерный массив
	//double dArray[4][3][3] так, как показано на рисунке и напишите фрагмент
	//кода, который меняет местами значения элементов четных
	//и нечетных слоев:
	//	было:			     |--------|
	//  				   / |4  4  4 |
	//					 |--------|	4 |
	//				   / |3  3  3 |	4 |
	//    			 |---------|3 |   |
	//			   / | 2  2  2 |3 | /
	//			  |---------|2 |__|
	//			  | 1  1  1 |2 | /
	//			  | 1  1  1 |__|
	//			  | 1  1  1 | /
	//			  |_________|

	//	стало:			     |--------|
	//  				   / |3  3  3 |
	//					 |--------|	3 |
	//				   / |4  4  4 |	3 |
	//    			 |---------|4 |   |
	//			   / | 1  1  1 |4 | /
	//			  |---------|1 |__|
	//			  | 2  2  2 |1 | /
	//			  | 2  2  2 |__|
	//			  | 2  2  2 | /
	//			  |_________|
	cout << "task 6" << endl;
	const int layer = 4;
	const int row = 3;
	const int element = 3;
	double dArray[layer][row][element];
	cout << "original array" << endl;
	for (int i = 0; i < layer; i++) {
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < element; k++) {
				dArray[i][j][k] = i + 1;
				cout << dArray[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	for (int i = 0; i < layer; i = i + 2)
	{
		//Замечание: НЕ НУЖНО МОДИФИЦИРОВАТЬ ВЫРАЖЕНИЯ СПРАВА ОТ ЗНАКА РАВЕНСТВА!!!
		double(*chet_p)[row][element] = &dArray[i];
		double(*nechet_p)[row][element] = &dArray[i + 1];
		//переставляем местами элементы i-того и i+1-ого слоев
		for (int m = 0; m < row; m++) {
			for (int n = 0; n < element; n++) {
				double temp = (*chet_p)[m][n];
				(*chet_p)[m][n] = (*nechet_p)[m][n];
				(*nechet_p)[m][n] = temp;
			}
		}
	}
	cout << "modified array" << endl;
	for (int i = 0; i < layer; i++) {
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < element; k++) {
				cout << dArray[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}


	///////////////////////////////////////////////////////////////////////////
	//Задание 7а. Объявите двухмерный встроенный массив элементов типа char.
	//Сформируйте значения элементов массива с помощью генератора случайных
	//чисел таким образом, чтобы в массиве были только символы '*' и '_'
	{
		cout << "task 7a" << endl;
		cout << "original array" << endl;
		const int row = 5;
		const int column = 10;
		char dStars[row][column];
		int counter_0[row]{};
		srand(static_cast<int>(time(0)));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				int rvalue = rand() % 2; //генерируем 0 или 1: 0 - '*', 1 - '_'
				if (rvalue == 0) {
					dStars[i][j] = '*';
					counter_0[i]++;
				}
				else dStars[i][j] = '_';
				cout << dStars[i][j] << " ";
			}
			cout << endl;
		}
		//В каждой строке "сдвиньте звездочки" в начало строки, например:
		//было - '*' '_' '_' '*' '*' '_' '*' '_' '*' '_'
		//стало: '*' '*' '*' '*' '*' '_' '_' '_' '_' '_'
		//и распечатайте массив по строкам - "постройте распределение"
		cout << "modified array" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				while (counter_0[i]) {
					dStars[i][j] = '*';
					cout << dStars[i][j] << " ";
					counter_0[i]--;
					j++;
				}
				dStars[i][j] = '_';
				cout << dStars[i][j] << " ";
			}
			cout << endl;
		}
	}
		// 7б. Модифицируйте предыдущее задание следующим способом:
		//После заполнения массива с помощью генератора случайных чисел
		//"сдвиньте" звездочки по столбцам вниз и распечатайте полученное
		//"распределение"
	{
		cout << "task 7b" << endl;
		const int row = 5;
		const int column = 10;
		char dStars_Columns[row][column];
		srand(static_cast<int>(time(0)));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				int rvalue = rand() % 2; //генерируем 0 или 1: 0 - '*', 1 - '_'
				if (rvalue == 0) {
					dStars_Columns[i][j] = '*';
				}
				else dStars_Columns[i][j] = '_';
			}
		}
		cout << "modified array" << endl;
		for (int j = 0; j < column; j++) {
			int s_counter = 0;
			for (int i = 0; i < row; i++) {
				if (dStars_Columns[i][j] == '*') {
					dStars_Columns[s_counter][j] = '*';
					if (s_counter != i) { dStars_Columns[i][j] = '_'; }
					s_counter++;
				}
			}
			for (int i = s_counter; i < row; i++) {
				dStars_Columns[i][j] = '_';
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cout << dStars_Columns[i][j] << " ";
			}
			cout << endl;
		}
	}

	//return 0;
}