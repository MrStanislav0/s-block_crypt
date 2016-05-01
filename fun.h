#ifndef MODULE3_H
#define MODULE3_H

struct pair_text
{
	string x; //генерируется
	string x_; //х_=x XOR А
	string y; // зашифрованный х
	string y_; // зашифрованный y_
	string C; // y xor y_
};

map <int, int> generate_pbox(int n, int m);//Cоздает таблицу замены размер n*m - 2. Используем во время xor с ключом. Таблица еще не перемешана, мешаем в swap
map <int, int> Mix_pbox(map <int, int> tabl, int n,int m);//Перемешивает таблицу замены. Получим p-блок

vector <string> generate_key(int n, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки s-блок


string Random_Bits(int n); // Генерирование случайной последовательности 0 и 1 n-штук

vector <string> divide_str(string str, int n); //Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
vector <string> use_s_box (vector <string> hs, map <string,string> sbox);//Заменяем sblok

string use_p_box (vector <string> hs,map<int,int>p_box);//перестановка строки согласно p_box

//XOR, согласно p_box

string help_xor (string a,string b);//создано, чтобы делать XOR двух строк и не заморачиваться, используется в create_dif_tabl, из-за свойства xor (a xor b = c --> a xor c = b)

string Int_to_BitStr(int n, int bit);

string crypto (int n, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box,string text);

vector <pair_text> create_pair ( int count, int n, int m, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box, string delta_A);//создает count штук пар открытых - закрытых текстов. Count задает пользователь

string Random_Bits_no_multi(int n, map <string, int> temp);

double dRand(double dMin, double dMax);

string Use1_sbox(map <string, string> sbox, string s1);

map <string, map<string, int>> Analyse_Tabl_generate(map <string, string> sbox, int m);


struct polynom
{
	vector <int> lenta; // случайная последовательность сгенерированная rand()%
	int N; // Количество битов в последовательности
	vector <int> numbers; // Вектор с позициями битов, которые надо XOR'ить в result_polynom
};

struct Result_random
{
	polynom liniya_svyazi; // Первый полином
	polynom liniya_svyazi2; // Второй полином
	int bit; // Случайный бит
	vector <int> bits; // Случайные биты
};

polynom generate_polynom(int x1, int x2, int x3 = 0, int x4 = 0, int x5 = 0); // Генерация полинома
polynom result_polynom(polynom liniya_svyazi); // Результат работы полинома (xor битов и сдвиг)
Result_random Random_Bits(polynom liniya_svyazi, polynom liniya_svyazi2, int n); // Генерирование псевдослучайной последовательности длины n
Result_random random_bit(polynom liniya_svyazi, polynom liniya_svyazi2); // Генерирование псевдослучайного бита
vector <int> sdvig(vector <int> &text_sdvg); // Функция сдвига вправо на 1 позицию

string IntVec_to_Str(vector <int> vec);
#endif 
