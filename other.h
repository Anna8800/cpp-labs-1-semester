
//Прототипы используемых в данном задании функций:
extern int& ref; //объявление внешней переменной, определенной в другом модуле
const int N = 4, M = 5;

int IncByValue(int);
void IncByPointer(int*);
void IncByReference(int&);
void swap(int*, int*);
void swap(int&, int&);
int findMin(int ar[][M], int);
int findMin(int **, int, int );
char MyStrCmp(const char*, const char*);
int DayOfYear(int, int, int, int ar[][12]);
void DayOfMonth(int, int, int, int (&ar)[2][12], int*, int*);
void Unique_Value(int *& ar, int&, int);
void Print_arr(const int ar[], int);
int Recursive_f(int);
void VarArgs(int, ...);
void VarArgsMacros(int, ...);
int* MyMin(int arr[], int );