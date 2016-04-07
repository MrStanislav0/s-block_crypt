#include <iostream>
#include <vector>
#include <map>
using namespace std;

map <int,int> swap (map <int,int> tabl, int count);
map <int,int> generate_tabl (int count);
vector <int> generate_key (int n, int m, int j);
vector < vector <int> > sub (vector<int> key, int n, int m, int j);

int main()
{
	int n,m,j;
	cin>>n>>m>>j;
	vector <int> key;
	key = generate_key(n,m,j);	
	for (int i=0; i<n*m*j; i++)
		cout<<key[i];
	

	return 0;
}
map <int,int> swap (map <int,int> tabl, int count)
{
	for (int i=0; i<count; i++)
		swap(tabl[i], tabl[rand() % count]);// генерируем таблицу замены
	return tabl;
}
map <int,int> generate_tabl (int count)
{
	map <int,int> a;
	for (int i=0; i<count; i++)
		a[i]=i;
	return a;
}

vector <int> generate_key (int n, int m, int j)
{
	vector <int> key;
	int r;
	for (int i=0;i<n*m*j;i++) //Генерируем ключ
	{
		r=rand()%2; //собственно сгенерировали число, взяли остаток от деления на 2 (хз верно или нет)
		key.push_back(r);// запихиваем в массив
	}
	return key;
}

vector <vector<int>> sub (vector<int> key,int n,int m, int j)
{
	vector <vector <int>> sub_key;
	int counter=0;

	sub_key.resize(j); // без этого не работает (??!??!!!)
	for (int i = 0; i<n; i++)// В цикле от 1 до n (n штук)
	{
		sub_key[i].resize(n*m);
		for (int k=0; k<n*m; k++) // В цикле от 1 до m (размер m)
		{
			sub_key[i].push_back(key[counter]);
			counter++;
		}
	}
	return sub_key;
}
