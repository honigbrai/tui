
#include <iostream>
#include <termios.h>
#include <unistd.h>


using namespace std;

void scrst();

void scren();

void scrsav();

void scrrest();

void scrclear();

void inviscurs();

void viscurs();

void homcurs();

void hlon();

void hloff();

void movcurs(int, int);

void enrawmod();

void disrawmod();

void getch();

void clrln();

int winsiz(int *, int *);

int poscurs(int *, int *);

void line(char, int, int, int, int);