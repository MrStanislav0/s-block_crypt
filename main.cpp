#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

#include "Sfiles.h"// создано для ввода-вывода из файла
#include "fun.h"

/*
Пусть будет - чтобы не лазить тыщу раз за функциями (какая, что делает)
если сильно мешает - убрать

map <int, int> generate_tabl(int, int);//Cоздает таблицу замены размер n*m - 2. Используем во время xor с ключом. Таблица еще не перемешана, мешаем в swap
map <int, int> swap(map <int, int> tabl, int, int);//Перемешивает таблицу замены.
vector <int> generate_key(int n, int m, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)
vector < vector <int> > sub(vector<int> key, int n, int m, int j); //Разбиваем ключ на K(i)
int Counter_Bits(vector <string> &text); //Подсчет битов в тексте
string Random_Bytes(int m); //Генерация случайной последовательности 0 и 1 длины m

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки sbox

string generate_text (int, int); //Создано для тестов. Генерирует строку n*m из 0 и 1. По сути - открытый текст
vector <string> sub_str_blok (string, int);//Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
*/

int main()
{
	srand(time(0));// делаем, дабы был ГСЧ нормальным, а не как обычно (начальное значение случайное)

	int n,m,j; //Кол-во блоков, размер блока, количество раундов
	vector <int> key;//Ключ
	vector <vector <int>> sub_key;//Разбитый ключ
	map <string,string> sbox;//С-блоки
	map<int,int> p_box;//таблица замены, она же функция подстановки (перед XOR)
	string text;

	
	cin>>n>>m>>j;
	
	key=generate_key(n, m, j);
	sub_key=sub(key,n,m,j);
	
	
	sbox=generate_sbox(m);
	sbox=generate_tabl_mix(sbox,m);

	p_box=generate_tabl(n,m);
	p_box=swap(p_box,n,m);

	text=generate_text (n,m);
	

	return 0;
}
