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

vector <pair_text> create_pair ( int count, int n, int m, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box,string text, string delta_A);//создает count штук пар открытых - закрытых текстов. Count задает пользователь

*/

#include "Sfiles.h"// Работа с файлами
#include "fun.h" // Все остальные функции

polynom pol1;
polynom pol2;

int main()
{
	/*
	string a, b;
	cin >> a >> b;
	string c = help_xor(a, b);
	cout << c;
	*/
	setlocale(LC_ALL, "Russian");
	//string name;
	//cin >> name;
	long long int g = 500;

	srand(g);

	// Пример работы нового генератора псевдослучайных чисел

	pol1 = generate_polynom(49, 22, 0); // x^49 + x^22 + 1
	pol2 = generate_polynom(142, 21, 0); // x^142 + x^21 + 1

	int n; // Кол-во блоков
	int m; // Размер блока
	int j; // Кол-во раундов
	int count; // Кол-во открытых-закрытых пар текстов

	string text; // Исходный текст
	string new_text; // Зашифрованный текст
	
	map <string, map<string, int>> Table_analysis; // Таблица анализа блока замены
	vector <pair_text> pair;

	cin >> n >> m >> j;
	cin >> text;
	
	vector <string> key = generate_key(n*m, j); // Генерация ключа
	map <string, string> s_box = generate_sbox(m); // Генерация s-блока (таблицы замены)
	map <int, int> p_box = generate_pbox(n, m); // Генерация p-блока (таблицы перестановки)

	string name = "D:\lol.txt";
	outpute_file_full(name, m, n, j, s_box, p_box);

	string now;
	for (int i = 0; i < (int)key.size(); i++)
	{
		now = now + key[i];
	}

	cout <<"Key "<< now << endl;
	
	Result_random test = Random_Bits(pol1, pol2, n*m);
	pol1 = test.liniya_svyazi; // изменяем полиномы
	pol2 = test.liniya_svyazi2;

	//text = IntVec_to_Str(test.bits); // Генерация текста (тестовая функция)
	new_text = crypto (m, n, j, key, s_box, p_box, text);//шифрование 
	/*
	Table_analysis = Analyse_Tabl_generate(s_box, m); // Таблица анализа блока замены

	string delta_A; // Генерация разности, пока что одной. Размер n*m, тот же что и у текста
	//cin >> delta_A;

	//cin >> count;
	pair = create_pair (count, n, m, j, key, s_box, p_box, delta_A); //создает count штук пар открытых - закрытых текстов. Count задает пользователь
	*/
	return 0;
}
