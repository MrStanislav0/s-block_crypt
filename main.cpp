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
map <int, int> generate_tabl(int n, int m);//Cоздает таблицу замены размер n*m - 2. Используем во время xor с ключом. Таблица еще не перемешана, мешаем в swap
map <int, int> swap(map <int, int> tabl, int n, int m);//Перемешивает таблицу замены.
vector <int> generate_key(int n, int m, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)
vector < vector <int> > sub(vector<int> key, int n, int m, int j); //Разбиваем ключ на K(i)
int Counter_Bits(vector <string> &text); //Подсчет битов в тексте
string Random_Bytes(int m); //Генерация случайной последовательности 0 и 1 длины m

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки sbox

string generate_text (int n, int m); //Создано для тестов. Генерирует строку n*m из 0 и 1. По сути - открытый текст
vector <vector <string>> sub_str_blok (string text, int n, int m);//Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
vector <vector <string>> use_s_box (vector <vector <string>> hs, map <string,string> s_box)

string XOR (vector <vector <string>> hs, map<int,int> p_box, vector< vector<int>> sub_key, int j);//собственно последние два блока, как я понял. XOR, согласно p_box
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
	map <string, map<string,int>> Ulia; //подсчет C исходя из dif
	
	
	cout << "Введите через пробел количество блоков, размер блока и количество раундов" << endl;
	cin >> n >> m >> j;
	
	vector <vector <int>> key = generate_key(n, m, j); // Генерация ключа
	
	
	map <string, string> s_box = generate_sbox(m); // Генерация s-блока (таблицы замены)

	map <int, int> p_box = generate_pbox(n, m); // Генерация p-блока (таблицы перестановки)

	text = generate_text (n,m); // Генерация текста (тестовая функция)
	vector <vector <string>> hs = sub_str_blok(text,n,m); // Разбиение текста на блоки
	
	for (int h = 0; h < hs.size(); h++) //по частям частей
	{
		for (int i = 0; i < j; i++) // по раундам
		{
			hs[h] = use_s_box(hs[h], s_box); // Применение s-блока
			string p_str = use_p_box(hs[h], p_box); // Применение p-блока
			string sub_key_in_str = int_to_str(key[i]);
			new_text = help_xor(p_str, sub_key_in_str);
			hs[h] = sub_block(new_text, n, m);//записываем полученное значение
		}
	}

	dif = create_dif_tabl(m);// создаем таблицу такую
	Ulia = create_tabl_count_diff(dif, s_box, m); // Таблица анализа блока замены

	// Вывод в файл

	string name;
	cout << "Напишите полный путь к файлу, в который хотите сохранить результат работы программы" << endl;
	cin >> name;
	cout << endl;

	outpute_info(name, m, n, j, 1);

	string temp;
	temp = "Исходные данные:";
	outpute_file(name, temp, 2);
	outpute_file(name, text, 2);

	temp = "Полный ключ:";
	outpute_file(name, temp, 2);
	outpute_file(name, key, 2);

	temp = "S-блок:";
	outpute_file(name, temp, 2);
	outpute_file(name, s_box, 2);

	temp = "P-блок:";
	outpute_file(name, temp, 2);
	outpute_file(name, p_box, 2);

	temp = "Зашифрованные данные:";
	outpute_file(name, temp, 2);
	outpute_file(name, new_text, 2);

	temp = "Таблица анализа блока замены:";
	outpute_file(name, temp, 2);
	outpute_file(name, Ulia, 2);

	cout << "Результат успешно записан в " << name << endl;

	return 0;
}
