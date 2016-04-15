#ifndef MODULE2_H
#define MODULE2_H
/*! Функция ввода текста из файла


Данная функция построчно считывает все строки из введенного файла и записывает в vector.
* \param [in] name ? имя файла
* \return Вектор с полным текстом из файла

*/
vector <string> inpute_file(string name);

/*! Функция проверяет, существует ли файл


Данная функция проверяет существует ли файл, если существует возвращает 1, в протичном случае 0.
* \param [in] name ? имя файла
* \return 1 или 0

*/
int Is_file(string name);
/*! Функция для записи в файл


Данная функция записывает в файл весь текст, который находится в vector. Есть 2 режима: mode = 1 (по умолчанию) - это запись в чистый файл. mode = 2 - режим записи в конец файла.
* \param [in] name ? имя файла
* \param [in] &text ? текст
* \param [in] mode ? номер режима (необязательный параметр)

*/
void outpute_file(string name, vector <string> &text, int mode = 1);

void outpute_file(string name, string text, int mode = 1);

void outpute_file(string name, map <string, string> s_box, int mode);

void outpute_file(string name, map <int, int> p_box, int mode);

void outpute_file(string name, vector <vector <int>> key, int mode);

void outpute_file(string name, map <string, map<string, int>> tabl, int mode);

void outpute_info(string name, int m, int n, int j, int mode);

#endif 