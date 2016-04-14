#ifndef MODULE3_H
#define MODULE3_H

struct difference //создано, для того, чтобы считать разность: x XOR y = z --> map <string, vector<difference>>
{
	string x;
	string y;
};

map <int, int> generate_tabl(int n, int m);//Cоздает таблицу замены размер n*m - 2. Используем во время xor с ключом. Таблица еще не перемешана, мешаем в swap
map <int, int> swap(map <int, int> tabl, int n,int m);//Перемешивает таблицу замены. Получим p-блок

vector <int> generate_key(int n, int m, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)
vector <vector<int>> sub(vector<int> key,int n,int m, int j); //Разбиваем ключ на K(i)
int Counter_Bits(vector <string> &text); //Подсчет битов в тексте
string Random_Bits(int m); //Генерация случайной последовательности 0 и 1 длины m, то есть текста

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки s-блок


string generate_text (int, int); //Создано для тестов. Генерирует строку n*m из 0 и 1. По сути - открытый текст

vector <vector <string>> sub_str_blok (string str,int n, int m);//Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
vector <string> use_s_box (vector <string> hs, map <string,string> sbox);//Заменяем sblok

string use_p_box (vector <string> hs,map<int,int>p_box);//перестановка строки согласно p_box
string int_to_str (vector <int> sub_key);
string sbox_str (string str,  map <string,string> sbox);
vector <string> sub_block (string str,int n,int m);
//XOR, согласно p_box

string help_xor (string a,string b);//создано, чтобы делать XOR двух строк и не заморачиваться, используется в create_dif_tabl, из-за свойства xor (a xor b = c --> a xor c = b)
map <string, vector<difference>> create_dif_tabl (int m);

#endif 
