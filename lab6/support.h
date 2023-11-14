#pragma once
#include "support.h"
#include "book_collection.h"
#include "book.h" 

void init_readme(); //+
void perm_delete(Library& library, int& Number, int& indexBook); 
int valid_number(Library& library, int definit, int init_number); 
void input_category(int& categor); 
void warning_empty_file(); //+
void warning_empty_library(); //+
void warning_existence_check(); //+
void choise_field_to_sort(Library& library); 
int getNumCategories(const char* arr[]);