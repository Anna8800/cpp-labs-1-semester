#include "book.h"
#include "book_collection.h"
#include "support.h"
#include <iostream>
#include <cstdio>

//метод сортировки - вставками

enum sort_field {
	author,
	title,
	year,
	price,
	categor_of_book,
};

float compare_title(const BOOK& first, const BOOK& second) { //сравнение по названию
	return static_cast<float>(strcmp(first.title, second.title));
}

float compare_author(const BOOK& first, const BOOK& second) { //сравнение по автору
	return static_cast<float>(strcmp(first.author, second.author));
}

float compare_year(const BOOK& first, const BOOK& second) { //сравнение по году
	return static_cast<float>(first.year - second.year);
}

float compare_price(const BOOK& first, const BOOK& second) { //сравнение по цене
	return static_cast<float>(first.price - second.price);
}

float compare_category(const BOOK& first, const BOOK& second) { //сравнение по категории
	return static_cast<float>(first.category - second.category);
}

float (*comparator[])(const BOOK&, const BOOK&) = { //массив указателей на функции сравнения
	compare_title,
	compare_author,
	compare_year,
	compare_price,
	compare_category
};

void sortLibrary(Library& library, float(*comparator)(const BOOK&, const BOOK&)) {
	int number = library.number;
	BOOK** book_arr = library.books;
	for (int i = 1; i < number; i++) {
		BOOK* tmp = book_arr[i];
		int j = i - 1;
		for (j; j >= 0 && comparator(*book_arr[j], *tmp) > 0; j--) {
			book_arr[j + 1] = book_arr[j];
		}
		book_arr[j + 1] = tmp;
	}
	printf("Sorting is completed!\n");
}
