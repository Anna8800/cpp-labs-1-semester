enum class Category {
	CLASSIC,
	SCIENCE_FICTION,
	FAIRY_TALE,
	SHORT_STORIES,
};
struct BOOK {
	char author[50];
	char title[100];
	short year;
	int price;
	Category category;
};

//Прототипы используемых в данном задании функций:
double Sum(double, double);
double Sub(double, double);
double Mul(double, double);
double Div(double, double);
void Sort(char* pcFirst, int nNumber, int size,
	void (*Swap)(void*, void*), int (*Compare)(void*, void*));
void SwapInt(void* p1, void* p2);
int CmpInt(void* p1, void* p2);
void Print_arr(const int ar[], size_t);
void Print_arr(const double ar[], size_t);
void SwapDouble(void* p1, void* p2);
int CmpDouble(void* p1, void* p2);
void SwapStr(void* p1, void* p2);
int CmpStr(void* p1, void* p2);
void Print_arr(const char* arr[], size_t);
const char* GetString1();
const char* GetString2();
const char* GetString3();
const char* GetString4();
const char* GetString5();
char* Cut_off_string(const char* origin, int length, char* slice);
void Print_book(const BOOK &book);
const char* categor_str(Category category);
void Fill_struct(BOOK& book);
