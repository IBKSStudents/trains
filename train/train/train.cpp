#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

long long StrToInt(char *ss) {
	long long i = 0, ii = 0;
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

long long intLi(char s[1000]) {
	long long w = 0, dot = 0;
	char chisla[11] = "0123456789";
	while (s[w]) {
		for (long long i = 0;i < 10;i++) {
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
	long long light = 0;
};
typedef trains *Ptrain;

Ptrain prev = NULL, end = NULL, train = NULL;

void AddFirst(Ptrain &Head, Ptrain Newbd)
{
	Newbd->next = Head;
	Head = Newbd;
	end = Head;
	Head->previous = Head;
	Head->next = end;
}

void add(Ptrain &Head, Ptrain Newbd)
{
	Ptrain q = Head;
	if (Head == NULL) { // если список пуст,
		AddFirst(Head, Newbd); // вставляем первый элемент
		return;
	}
	Ptrain e;
	while (q->next != end) q = q->next; // ищем последний элемент
	Newbd->next = end;
	Newbd->previous = q;
	q->next = Newbd;
	q = Head;
	q->previous = q->next;
}

void pr() {
	if (train != NULL) {
	end = train;
	Ptrain q = train;
	do { printf("%d", q->light); q = q->next; } while (q != end);
	printf("\n\n");
}
}

void ins() {
	Ptrain tr = train, one;
	train = NULL;
	end = train;
	FILE *f = fopen("config.txt", "r");
	char c = 'n', s[2];
	while (!feof(f)) {
		c = fgetc(f);
		if (feof(f)) break;
		one = new trains;
		s[0] = c;
		s[1] = '\0';
		if (StrToInt(s)) one->light = 1;
		add(train, one);
	}
	fclose(f);
}

void counts() {
	char ss[1000];
	clock_t time = clock();
		printf("Input count (after 9 simbol will cut):\n");
		ss[0] = '\0'; gets_s(ss, 999);
		ss[9] = '\0';
		long long u = StrToInt(ss);
		while ((intLi(ss) == 0)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			ss[0] = '\0'; gets_s(ss, 999);
			u = StrToInt(ss);
		}
		train = NULL;
		Ptrain tr = end, one;
		long long count = 0;
		while (count++!=u) {
			one = new trains;
			add(train, one);
		}
		long long t = (clock() - time);
		int ms = t % 1000;
		t /= 1000;
		int sec = t % 60;
		t /= 60;
		int min = t;
		printf("Time - %d m %d s %d ms\n", min, sec, ms);
}

void sets() {
	if (train == NULL) {
		printf("Create trains\n");
		return;
	}
	char ss[1000];
	Ptrain tr = end, one;
	do {
		system("cls");
		printf("0 - no light\n1 - light\n\n2 - if you want to set all other 0\n3 - if you want to set all other 1\n4 - if you want to set other random\n5 - to exit\n");
		ss[0] = '\0'; gets_s(ss, 999);
		long long u = StrToInt(ss);
		while ((intLi(ss) == 0)) {
		repeatss:;
			printf("Вы ввели неверное число. Повторите ввод:");
			ss[0] = '\0'; gets_s(ss, 999);
			u = StrToInt(ss);
		}
		if ((u < 0) || (u > 3)) goto repeatss;
		long long count = 0;
			one = new trains;
			if (u == 0) tr->light = 0;
			if (u == 1) tr->light = 1;
			if (u == 2) {
				return;
			}
			if (u == 3) {
				do {
					tr->light = 1;
					tr = tr->next;
				} while (tr != end);
				return;
			}
			if (u == 4) {
				do {
					tr->light = rand() % 2;
					tr = tr->next;
				} while (tr != end);
				return;
			} 
			if (u == 5) return;
			tr = tr->next;
	} while (tr!=end);
}

void algs() {
	clock_t time = clock();
	Ptrain tr = end;
	while (1) {
		long long count = 0, l = 0;
		count = 0;
		l = tr->light;
		tr->light = (l + 1) % 2;
		do {
			tr->light = (l + 1) % 2;
			tr = tr->next;
			count++;
		} while (tr->light == l);
		if(tr==end) { 
			printf("Count - %d\n", count);
			long long t = (clock() - time);
			int ms = t % 1000;
			t /= 1000;
			int sec = t % 60;
			t /= 60;
			int min = t;
			printf("Time - %d m %d s %d ms\n", min, sec, ms);
			return;
		}
		else {
			while (tr != end) tr = tr->previous;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	long long com = -1,	 // Command number
		u = -20,	 // Just needed
		kolKom = 5;	 // Count of commands
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Input command:\n");
		printf("0 - Read config from file\n");
		printf("1 - Set count of trains\n");
		printf("2 - Set config of trains\n");
		printf("3 - Start algorithm\n");
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
		if (u == 2) sets();
		if (u == 3) algs();
		if (u == 4) pr();
	}
    return 0;
}

