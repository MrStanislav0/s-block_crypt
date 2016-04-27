#ifndef MODULE2_H
#define MODULE2_H

struct data_file
{
	int m; //генерируется
	int n;
	int j;
	map <string, string> s_box;
	map <int, int> p_box;
};

int Is_file(string name); // Проверка существования файла

void outpute_file_full(string name, int m, int n, int j, map <string, string> s_box, map <int, int> p_box); // Вывод всех данных в файл
void outpute_info(string name, int m, int n, int j, int mode); // Вывод m, n, j 
void outpute_sbox(string name, map <string, string> s_box, int mode); // Вывод s-блока
void outpute_pbox(string name, map <int, int> p_box, int mode); // Вывод p-блока

data_file inpute_file_full(string name); // Ввод всех данных
#endif