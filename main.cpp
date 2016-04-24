#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <clocale>

using namespace std;

/*
vector <string> divide_str(string str, int n); //Разбивает текст на кучу блоков для дальнейшей замены

vector <int> generate_key(int n, int m, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)
vector < vector <int> > sub(vector<int> key, int n, int m, int j); //Разбиваем ключ на K(i)

string Random_Bytes(int m); //Генерация случайной последовательности 0 и 1 длины m

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки sbox

string generate_text (int n, int m); //Создано для тестов. Генерирует строку n*m из 0 и 1. По сути - открытый текст
vector <vector <string>> sub_str_blok (string text, int n, int m);//Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
vector <vector <string>> use_s_box (vector <vector <string>> hs, map <string,string> s_box)

string help_xor (string a,string b);//создано, чтобы делать XOR двух строк 

string XOR (vector <vector <string>> hs, map<int,int> p_box, vector< vector<int>> sub_key, int j);//собственно последние два блока, как я понял. XOR, согласно p_box

string crypto (int n, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box,string text)

vector <string> ulia (int n, int j, string delta_A,  map <string, map<string, int>> Table_analysis, map <int, int> p_box)
*/

#include "Sfiles.h"// Работа с файлами
#include "fun.h" // Все остальные функции


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	int n; // Кол-во блоков
	int m; // Размер блока
	int j; // Кол-во раундов

	string text; // Исходный текст
	string new_text; // Зашифрованный текст
	map <string, vector<difference>> dif;//тут будут хранится: (2^m штук значений) 000 = x XOR y (что надо XOR, чтобы заработало) --> смотри алгоритм Липилина, если непонятно
	map <string, map<string, int>> Table_analysis,open; //подсчет C исходя из dif
	
	cin >> n >> m >> j;
	
	vector <string> key = generate_key(n*m, j); // Генерация ключа
	map <string, string> s_box = generate_sbox(m); // Генерация s-блока (таблицы замены)
	map <int, int> p_box = generate_pbox(n, m); // Генерация p-блока (таблицы перестановки)


	text = Random_Bits (n*m); // Генерация текста (тестовая функция)
	new_text = crypto (n, j, key, s_box, p_box, text);//шифрование 


	dif = create_dif_tabl(m);// создаем таблицу такую
	Table_analysis = create_tabl_count_diff_version2(dif, s_box, m); // Таблица анализа блока замены


	string delta_A; // Генерация разности, пока что одной. Размер n*m, тот же что и у текста
	cin>>delta_A;
	

	map <int,vector<string>> uliana;
	uliana = ulia (n, j, delta_A, Table_analysis, p_box);
	return 0;
}
