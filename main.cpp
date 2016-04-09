#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

#include "Sfiles.h"// создано для ввода-вывода из файла
#inckude "fun.h"



int main()
{
	srand(time(0));

	map <string, string> sbox = generate_sbox(3);
	map <string, string> table = generate_tabl_mix(sbox, 3);

	

	return 0;
}

