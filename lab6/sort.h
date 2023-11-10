#pragma once
#include "book_collection.h"
#include "book.h"

float compare_title(const BOOK& first, const BOOK& second);
float compare_author(const BOOK& first, const BOOK& second);
float compare_year(const BOOK& first, const BOOK& second);
float compare_price(const BOOK& first, const BOOK& second);
float compare_category(const BOOK& first, const BOOK& second);
extern float (*comparator[])(const BOOK&, const BOOK&);
void sortLibrary(Library& library, float(*comparator)(const BOOK&, const BOOK&));