# include "./malloc.h"

#define M (1024 * 1024)

int main()
{
    void* a = malloc(1);
	write(1, "a\n", 2);
    void* b = malloc(2);
	write(1, "b\n", 2);
    void* c = malloc(4);
	write(1, "c\n", 2);
    void* d = malloc(8);
	write(1, "d\n", 2);
    void* e = malloc(16);
	write(1, "e\n", 2);
    void* f = malloc(32);
	write(1, "f\n", 2);
    void* g = malloc(64);
	write(1, "g\n", 2);
    void* h = malloc(128);
	write(1, "h\n", 2);
    void* i = malloc(256);
	write(1, "i\n", 2);
    void* j = malloc(512);
	write(1, "j\n", 2);
    void* k = malloc(1024);
	write(1, "k\n", 2);
    void* l = malloc(1024 * 2);
	write(1, "l\n", 2);
    void* m = malloc(1024 * 4); 
	write(1, "m\n", 2);
    void* n = malloc(1024 * 32);
	write(1, "n\n", 2);
    void* o = malloc(M);
	write(1, "o\n", 2);
    void* p = malloc(16*M);
	write(1, "p\n", 2);
    void* q = malloc(128*M);
	write(1, "q\n", 2);
    show_alloc_mem(); 
	write(1,"End\n",4);
    return (0); 
}