#include "stdafx.h" //Подключение необходимых библеотек    
#include "conio.h"
#include "stdio.h"
#include "clocale"
#include "string.h"
#include "malloc.h"
#include "stdlib.h"
#include <windows.h>

using namespace System;
using namespace std;
using namespace System::IO;

struct z { // Шаблон для структуры исходных данных
char nazvanie[20]; //Название кинопроизведения
char city[20];//Название страны
char klass[20];//Название жанра
long kolvo;//Количество сезонов
long money;//Кассовый сбор
char data[20];//Дата выхода
};

struct sp { //структура, описание двустроннего списка названий студий с необходимыми доп. данными
char nazvanie[20];
char city[20];
long kolvo;
long money;
struct sp* sled;
struct sp* pred;
};

#define ENTER 13 //Создание обозначение кнопок 
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
#define LENGTHMENU 99

struct z *z = NULL;

int menu(int, char [][LENGTHMENU]); //шаблонны используеммых функций 
void maximinsr(struct z*, int);
void gorod(struct z*, int);
void text_data(char *,char *);
void kolvo(struct z *,int);
void alfalist(struct z*,struct sp** spisok,int);
void vstavka(struct z*,char*,struct sp** spisok, int);
void listing(struct z*,int);
void diagram(struct z*,struct sp** spisok,int);
void diagram2(struct z*,struct sp** spisok,int);
void newest(struct  z*,int);
void stdat(struct  z*,int);


void text_data(char *s,char *sd) // Функция для преобразования даты в текстовый формат
	{
	char s0[3],month[12][9]={ // задача массива с названиями месяцов
	"января","февраля","марта","апреля","мая","июня",
	"июля","августа","сентября","октября","ноября","декабря"};
	strcpy(s,sd+8);
	strcat(s," ");
	strncpy(s0,sd+5,2); s0[2]=0;
	strcat(s,month[ atoi(s0)-1]);
	strcat(s," ");
	strncat(s,sd,4);
	return;
	}
void first(struct z* kino, int NC)// Функция для нахождения самой старого фильма
	{
	int i;
	char s[17];
	struct z* best=kino;
	for(i=1;i<NC;i++)
	if (strcmp(kino[i].data,best->data)<0)
	best=&kino[i];
	text_data(s,best->data);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Самое старое кинопроизведение жанра %s с %ld сезонами ",
	best->klass,best->kolvo);
	Console::CursorLeft=10;
	Console::CursorTop=17;
	printf("В стране %s имеет название \"%s\" ",
	best->city, best->nazvanie);
	Console::CursorLeft=10;
	Console::CursorTop=18;
	printf("Выпущен %s ",s);
	getch();
	}

int main(array<System::String ^> ^args) //Главная программа осуществляет открытие файла и переносит их в выделенную память
	{
	int i,n, NC; // Инициализация переменных
	FILE *in; //Указатель на переменну для хранения данных из файла
	struct z *kinos; 
	char dan[][LENGTHMENU]={ 
	"Максимальное,минимальное и ср.значение кассовых сборов у кинопроизведений       ",
	"Сколько кинопроизведений было снято в США?                                      ",
	"Какой кинопроизведение появился в кино раньше всех?                             ",
	"Количество выпущенных нинопроизведений определенной стране по запросу           ",
	"Список кинопроизведений в жанре \"Приключение\", больше чем с 2 сезонами          ",
	"Алфавитный и обратный список кинопроизведений                                   ",
	"Диаграмма по кол-ву сезонов                                                     ",
	"Диаграмма по кассовым сборам                                                    ",
	"Кинопроизведение из одной страны,c одинаковым кол-во сезонов                    ",
	"Выход                                                                           "
	};
	setlocale(LC_CTYPE,"Russian"); //Установка локализации на руский язык
	Console::CursorVisible::set(false); // Скрытие курсора в консоли 
	Console::BufferHeight=720;
	Console::BufferWidth=1280;
	if((in=fopen("Films.txt","r"))==NULL) //Открытие файла с данными, и проверка на открытие
	{
		printf("\nФайл Films.txt не открыт !"); //Сообщение об ошибке открытия файла
		getch(); exit(1);
	}
	Console::CursorLeft=27;
	printf("Список кинопроизведений\n");
	printf(" \n");
	printf("Кинопроизведение      Страна        Сезоны   Кассовые сборы(млн)    Жанр    Дата выпуска \n");
	printf("_________________________________________________________________________________________\n");
	fscanf(in,"%d",&NC); // Считывание количества строк из файла
	kinos=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)
	fscanf(in,"%s%s%ld%ld%s%s", // Считывание данных из файла в структуру.
	kinos[i].nazvanie, kinos[i].city, &kinos[i].kolvo,
	&kinos[i].money, kinos[i].klass, kinos[i].data);
	for(i=0;i<NC;i++)
	printf("\n%-20s %-20s %2ld %10ld %20s %-20s", // Вывод данных об играх на экран
	kinos[i].nazvanie,
	kinos[i].city, kinos[i].kolvo,
	kinos[i].money,kinos[i].klass,
	kinos[i].data);
	struct sp *spisok = nullptr;
	struct sp2 *spisok2 = nullptr;
	getch();
	while(1)
	{
		Console::ForegroundColor=ConsoleColor::White; // Установка цвета фона 
		Console::BackgroundColor=ConsoleColor::DarkMagenta; // Установка цвета текста 
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::White; // Установка цвета фона 
		Console::BackgroundColor=ConsoleColor::Magenta;// Установка цвета текста 
		Console::CursorLeft=10;
		Console::CursorTop=4;
	printf("                                                                                  ");
	for(i=0;i<11;i++)
	{
	Console::CursorLeft=10;
	Console::CursorTop=i+5;
	printf(" %s ",dan[i]);
	}
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("                                                                                  ");
	n=menu(10, dan); //Использования функции меню 
	switch(n) {
		case 1: maximinsr(kinos, NC);break;
		case 2: gorod(kinos, NC);break;
		case 3: first(kinos, NC);break;
		case 4: newest(kinos, NC);break;
		case 5: listing(kinos, NC);break;
		case 6: alfalist(kinos,&spisok, NC);break;
		case 7: diagram(kinos,&spisok, NC);break;
		case 8: diagram2(kinos,&spisok, NC);break;
		case 9: stdat(kinos, NC);break;
		case 10: exit(0);

		}
	}
		return 0;
}
int menu(int n, char dan[][LENGTHMENU]) // Функция для работы с меню
	{
		int y1=0,y2=n-1; // Инициализация переменных для отслеживания текущей и предыдущей позиции меню 
		char c=1; // Инициализация переменной для хранения введенного символа
		while (c!=ESC) // Цикл продолжается, пока не нажата клавиша ESC
	{
	switch(c) {
			case DOWN: y2=y1; y1++; break; // Перемещение вниз по меню при нажатии клавиши "Стрелка вниз"
			case UP: y2=y1; y1--; break; // Перемещение вверх по меню при нажатии клавиши "Стрелка вверх"
			case ENTER: return y1+1; //Выбор вопроса при нажатии кнопки "ENTER"
			case HOME: y2=y1;y1=0;break; // Переход к первому пункту меню при нажатии кнопки "HOME"
			case END: y2=y1;y1=n-1;break; // Переход к последнему пункту меню при нажатии кнопки "END"
				}
	if(y1>n-1){y2=n-1;y1=0;} // Проверка границ меню и зацикливание
	if(y1<0) {y2=0;y1=n-1;}
	Console::ForegroundColor=ConsoleColor::Black; // Отображение текущего и предыдущего пункта меню с различными цветами
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Magenta;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch(); // Ожидание ввода символа для предотвращения автоматического выхода
	}
	exit (0); //Выход при нажатии кнопки "ESC"
	}
void maximinsr(struct z* kino, int NC){ //Функция для нахождения фильмов с наименьшим,максимальный и среднем значением кассовых сборов
int i=0;
struct z max;
	strcpy(max.nazvanie,kino[0].nazvanie);
	max.money=kino[0].money;
	for(i=1;i<NC;i++)
	if (kino[i].money>max.money)
	{
	strcpy(max.nazvanie,kino[i].nazvanie);
	max.money=kino[i].money;
	}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Самый большой кассовый сбор: %ld",max.money);
	Console::CursorLeft=10;
	Console::CursorTop=17;
	printf("У кинопроизведении: %s",max.nazvanie);


	int total = 0;
    double average = 0.0;
    for(int i = 0; i < NC; i++)
    {
        total += kino[i].money;
    }
    average = total / NC;
    
	Console::ForegroundColor = ConsoleColor::Black;
	Console::BackgroundColor = ConsoleColor::Cyan;
    Console::CursorLeft = 10;
    Console::CursorTop = 22;
    printf("Средний кассовый сбор у кинопроизведений: %0.2f", average);


	int ii=0; struct z min;
	strcpy(min.nazvanie,kino[0].nazvanie);
	min.money=kino[0].money;
	for(i=1;i<NC;i++)
	if (kino[i].kolvo<min.money)
	{
	strcpy(min.nazvanie,kino[i].nazvanie);
	min.money=kino[i].money;
	}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=10;
	Console::CursorTop=19;
	printf("Самый маленькийй кассовый сбор: %ld",min.money);
	Console::CursorLeft=10;
	Console::CursorTop=20;
	printf("У кинопроизведении: %s",min.nazvanie);

getch();
}
void gorod(struct z *kino, int NC)
{
int i,k=0;
for(i=0;i<NC;i++)
if (strcmp(kino[i].city,"США")==0)
k++;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Количесво снятых кинопроизведений в стране США: %d",k);
getch();
}
void alfalist(struct z* kino,struct sp** spisok, int NC) //Функция для отображения алфавитного списка фильмов
{
	int i;
	struct sp* nt, *z;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::Clear();
	printf("\n Алфавитный список всех кинопроизведений");
	printf(" \tОбратный алфавитный список всех кинопроизведений");
	printf(" \n");
	printf("\n\r     Кинопроизведение      Сезоны");
	printf("            \t      Кинопроизведение      Сезоны \n");
	printf("\n __________________________________");
	printf("\t         __________________________________\n");
	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(kino,kino[i].nazvanie,spisok, NC);
	for(nt=*spisok; nt!=0; nt=nt->sled)
	printf("\n %-20s %10ld",nt->nazvanie,nt->kolvo);

	for(nt=*spisok, z=0;nt!=0; z=nt,nt=nt->sled)
	Console::CursorTop=7;;

	 for(nt=z; nt!=0; nt=nt->pred){
		Console::CursorLeft=50;
		printf("%-20s %10ld",nt->nazvanie,nt->kolvo);
		Console::CursorTop+=1;
 }
getch();
}
void vstavka(struct z* kino,char* nazvanie,struct sp** spisok, int NC) // Функция для вставки кинопроивзеденицй в алфовитном порядке в список (двусторонний)
{
	int i;
	struct sp *nov,*nt,*z=0;
	for(nt=*spisok; nt!=0 && strcmp(nt->nazvanie,nazvanie)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->nazvanie,nazvanie)==0) return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->nazvanie,nazvanie);
	nov->sled=nt;
	nov->kolvo=0;
	nov->money=0;
	nov->pred=z;
	for(i=0;i<NC;i++)
		if(strcmp(kino[i].nazvanie,nazvanie)==0){
			nov->kolvo+=kino[i].kolvo;
			nov->money+=kino[i].money;}
	if(!z) *spisok=nov;
	if(z)z->sled=nov;
	if(nt) nt->pred=nov;
	return;
}
void newest(struct  z* kino, int NC) // Функция для отображения фильмов страны, удовлетворяющих определенным условиями
{
	Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::Clear();
int i, kolvo=0;
char city[20];
printf (" Список кинопроизведений из конкретной страны \n");
printf (" Введите название страны :");
Console::CursorLeft++;
Console::CursorVisible::set(true); //включаем курсор
SetConsoleCP(1251); //для считывания русских символов
scanf("%s",city);//вписываем нужный текст
SetConsoleCP(866); //кодировка консоли, чтобы могли выводить русские
Console::CursorVisible::set(false);
printf("\nКинопроизведение         Жанр       Сезоны   Кассовый сбор(млн)");
printf("\n========================================================== \n");
for (i=0;i<NC;i++)
{
if(strcmp(kino[i].city,city)==0)
{
printf("\n %-20s %-15s %-10d %-10d", kino[i].nazvanie, kino[i].klass,kino[i].kolvo,kino[i].money);
kolvo++;
}
}
if (kolvo==0) 
printf
("\n========================================================== \nКинопроизведения из данной страны не найдены");
if (kolvo)
printf("\n\n========================================================== \n");
printf("\nКол-во снытых кинопроизведений из интересующей страны: %-7d",kolvo);
getch();
return ;
}

void listing(struct z* kino, int NC)
{
int i;
struct z* nt;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::Clear();
printf("\n\r Список кинопроизведений в жанре \"Приключение\", больше чем с 2 сезонами");
printf(" \n");
printf("\n\r     Кинопроизведения             Сезоны \n\r");
printf("______________________________________________________\n");
for(i=0,nt=kino;i<NC;nt++,i++)
if (nt->kolvo>2 && strcmp(nt->klass,"Приключение")==0)
printf("\n\r %-20s %16ld ",nt->nazvanie,nt->kolvo);
getch();
}
void diagram(struct z *kino,struct sp** spisok, int NC) //Функция для отображения диаграммы по количеству сезонов
{
struct sp *nt;
int len,i,NColor;
long sum = 0 ;
char str1[20];
char str2[20];
System::ConsoleColor Color;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::Clear();
for(i=0;i<NC;i++) sum = sum+kino[i].kolvo ;
if(!*spisok)
for(i=0;i<NC;i++)
vstavka(kino,kino[i].nazvanie,spisok, NC);
Color=ConsoleColor::Black; NColor=0;
for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
{
sprintf(str1,"%s",nt->nazvanie);
sprintf(str2,"%3.1f%%",(nt->kolvo*100./sum));
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor= ConsoleColor::Cyan;
Console::CursorLeft=5; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=30;
printf("%s",str2);
Console::BackgroundColor=++Color; NColor++;
Console::CursorLeft=40;
for(len=0; len<nt->kolvo*100/sum; len++) printf(" ");
if(NColor==10)
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();

return ;
}
void diagram2(struct z *kino,struct sp** spisok, int NC)//Функция для отображения диаграммы по кассовым сборам
{
struct sp *nt;
int len,i,NColor;
long sum1 = 0 ;
char str1[20];
char str2[20];
System::ConsoleColor Color;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::Clear();
for(i=0;i<NC;i++) sum1 = sum1+kino[i].money ;
if(!*spisok)
for(i=0;i<NC;i++)
vstavka(kino,kino[i].nazvanie, spisok, NC);
Color=ConsoleColor::Black; NColor=0;
for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
{
sprintf(str1,"%s",nt->nazvanie);
sprintf(str2,"%3.1f%%",(nt->money*100./sum1));
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor= ConsoleColor::Cyan;
Console::CursorLeft=5; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=30;
printf("%s",str2);
Console::BackgroundColor=++Color; NColor++;
Console::CursorLeft=50;
for(len=0; len<nt->money*100/sum1; len++) printf(" ");
if(NColor==10)
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();

return ;
}
void stdat(struct z*kino, int NC)// Функция для сравнения сезонов и выявления из одной страны кинопроизведенения
{
int i, k, flag=0;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::CursorLeft=10;
Console::CursorTop=17;
for (k=0; k<NC; k++)
{
for (i=k+1; i<NC; i++)
{
if(strcmp(kino[i].city, kino[k].city)==0 && (kino[i].kolvo ==
kino[k].kolvo))
{
flag=1;
Console::CursorLeft=10;
printf(" Кинопроизведения '%s' и '%s' из страны '%s' имеют по %d сезонов\n",kino[i].nazvanie, kino[k].nazvanie, kino[i].city,kino[i].kolvo);
Console::CursorTop+=1;

}
}
break;}
if (!flag)
{
printf(" Совпадений не найдено!");
}
getch();
}