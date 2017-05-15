#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

int StrToInt(char *ss) {
	int i = 0, ii = 0;
	char *s = ss;
	while (*s) {
		ii = i;
		if (*s == '0') { i = 10 * i + 0; }
		if (*s == '1') { i = 10 * i + 1; }
		if (*s == '2') { i = 10 * i + 2; }
		if (*s == '3') { i = 10 * i + 3; }
		if (*s == '4') { i = 10 * i + 4; }
		if (*s == '5') { i = 10 * i + 5; }
		if (*s == '6') { i = 10 * i + 6; }
		if (*s == '7') { i = 10 * i + 7; }
		if (*s == '8') { i = 10 * i + 8; }
		if (*s == '9') { i = 10 * i + 9; }
		s++;
		//if (ii > i) return -1;
	}
	return i;
}

int intLi(char s[1000]) {
	int w = 0, dot = 0;
	char chisla[11] = "0123456789";
	while (s[w]) {
		for (int i = 0;i < 10;i++) {
			if (s[w] == chisla[i]) goto yes;
			if (s[w] == '.') {
				dot++;
				if (dot == 2) return 0;
				goto yes;
			}
		}
		return 0;
	yes:
		w++;
	}
	return 1;
}

struct trains {
	trains *previous;
	trains *next;
	int light = 0;
};
typedef trains *Ptrain;

Ptrain prev = NULL, end = NULL, train = NULL;

void ins() {
	Ptrain tr = train;
	end = train;
	FILE *f = fopen("config.txt", "r");
	char c = 'n', *s="";
	while (!feof(f)) {
		c = fgetc(f);
		if (feof(f)) break;
		s[0] = c;
		s[1] = '\0';
		if (StrToInt(s)) tr->light = 1;
		prev = tr;
		tr->next = NULL;
		tr = tr->next;
		prev->next = tr;
		tr->previous = prev;
		tr->next = NULL;
	}
	fclose(f);
	tr->next = end;
	end->previous = tr;
}

void counts() {
	int com = -1,	 // Command number
		u = -20,	 // Just needed
		kolKom = 2;	 // Count of commands
	char s[1000];
		com = -1;
		u = -20;
		printf("Input count:\n");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			u = StrToInt(s);
		}
		train = NULL;
		Ptrain tr = train;
		end = train;
		for (int ct = 0;ct < u;ct++) {
			prev = tr;
			tr->next = NULL;
			tr = tr->next;
			prev->next = tr;
			tr->previous = prev;
			tr->next = NULL;
		}
		tr->next = end;
		end->previous = tr;
}

int main()
{
	int com = -1,	 // Command number
		u = -20,	 // Just needed
		kolKom = 2;	 // Count of commands
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Input command:\n");
		printf("0 - Read config from file\n");
		printf("1 - Set count of trains\n");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			u = StrToInt(s);
		}
		system("cls");
		if (u > kolKom - 1) goto repeat; else
		if (u == 0) ins();
		if (u == 1) counts();
	}
    return 0;
}

