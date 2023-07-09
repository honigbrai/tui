#include "tui.h"

struct termios termioso;

void clrln(){
	cout << "\x1b[2K";
}

void disrawmod(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termioso);
}

void enrawmod() {
	tcgetattr(STDIN_FILENO, &termioso);
  
	struct termios raw = termioso;
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN );
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_cflag |= (CS8);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int poscurs(int *lines, int *cols){
	char buf[32];
	unsigned int i = 0;
	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if (buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[') return -1;
	if (sscanf(&buf[2], "%d;%d", lines, cols) != 2) return -1;
	return 0;
}

int winsiz(int *lines, int *cols){
	scrsav();
	
	movcurs(0,0);
	
	for(int i = 0; i < 999; ++i){
		cout << "0" << endl;
	}
	
	int temp;
	
	movcurs(0, 999);
	poscurs(lines, &temp);
	
	movcurs(0,0);
	
	for(int i = 0; i < 999; ++i){
		cout << "0";
	}
	
	movcurs(999, 0);
	
	if(poscurs(&temp, cols) != 0) return -1;
	
	scrrest();
	return 0;
}

void scrst(){
	cout << "\x1b[?1049h";
}

void scren(){
	cout << "\x1b[?1049l";
}

void scrsav(){
	cout << "\x1b[?47h";
}

void scrrest(){
	cout << "\x1b[?47l";
}

void scrclear(){
	cout << "\x1b[2J";
}

void inviscurs(){
	cout << "\x1b[?25l";
}

void viscurs(){
	cout << "\x1b[?25h";
}

void homcurs(){
	cout << "\x1b[H";
}

void hlon(){
	cout << "\x1b[7m";
}

void hloff(){
	cout << "\x1b[27m";
}

void movcurs(int line, int column){
	cout << "\x1b[" << line << ";" << column << "H";
}

void line(char c, int x0, int y0, int x1, int y1){
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; 
 
	while(true){
		movcurs(y0, x0);
		cout << c;
		
		if (x0 == x1 && y0 == y1) break;
		
		e2 = err + err;
		
		if (e2 >= dy) {
			err += dy; x0 += sx; 
		}
		if (e2 <= dx) {
			err += dx; y0 += sy;
		}
	}
}
