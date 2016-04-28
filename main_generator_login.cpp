#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

vector <char> generate_set();
string random_string(vector <char> random_set, int len);
vector <string> generate_logins(vector <char> random_set, int len, int n);
void outpute(string name, vector <string> vec_str, int mode = 1);


int main()
{
	srand(time(0));

	vector <char> random_set = generate_set();

	int len = 0;
	int n = 0;
	cin >> len >> n;

	vector <string> vec = generate_logins(random_set, len, n);

	string nem = "D:\hah4s.txt";
	outpute(nem, vec);

	return 0;
}

vector <char> generate_set()
{
	vector <char> set_random;
	
	for (int i = 33; i < 127; i++)
	{
		char temp = (char) i;
		set_random.push_back(temp);
	}

	random_shuffle(begin(set_random), end(set_random));

	return set_random;
}

string random_string(vector <char> random_set, int len)
{
	string str;

	for (int i = 0; i < len; i++)
	{
		int r = rand() % random_set.size();
		str = str + random_set[r];
	}
		
	return str;
}

void outpute(string name, vector <string> vec_str, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	for (int i = 0; i < vec_str.size(); i++)
	{
		out_file << vec_str[i] << endl;
	}

	out_file.close();
}

vector <string> generate_logins(vector <char> random_set, int len, int n)
{
	vector <string> vec_str;

	for (int i = 0; i < n; i++)
	{
		string s1 = random_string(random_set, len);
		vec_str.push_back(s1);
	}

	return vec_str;
}