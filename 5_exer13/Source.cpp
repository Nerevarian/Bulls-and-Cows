#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<windows.h>
#include<cstdlib>
#include<ctime>

using namespace std;


void cow(vector<int> game, int num0, int num1, int num2, int num3)
{
	int sum = 0;
	if (num0 == game[1] || num0 == game[2] || num0 == game[3]) ++sum;
	if (num1 == game[0] || num1 == game[2] || num1 == game[3]) ++sum;
	if (num2 == game[1] || num2 == game[0] || num2 == game[3]) ++sum;
	if (num3 == game[1] || num3 == game[2] || num3 == game[0]) ++sum;
	cout << "Коров " << sum << "\n\n";
}

bool bull(vector<int> game, int num0, int num1, int num2, int num3)
{
	int sum = 0;
	if (num0 == game[0]) ++sum;
	if (num1 == game[1]) ++sum;
	if (num2 == game[2]) ++sum;
	if (num3 == game[3]) ++sum;
	if (sum == 4)
	{
		cout << "Победа\n\n";
		return true;
	}
	cout << "Быков " << sum << '\n';
	cow(game, num0, num1, num2, num3);
	return false;
}

bool the_game(vector<int> game, int num)
{
	int num3 = num % 10;
	num /= 10;

	int num2 = num % 10;
	num /= 10;

	int num1 = num % 10;
	num /= 10;

	int num0 = num % 10;


	return bull(game, num0, num1, num2, num3);
}


vector<int> v_generator()
{
	vector<int> game;
	game.push_back(1+rand() % 9);
	while (game.size()<4)
	{
		bool repeat = false;
		int num = rand() % 10;
		for (int d : game) if (d == num) repeat = true;
		if (repeat == false) game.push_back(num); 
	}
	return game;
}

bool get_out(char leave)
{
	switch (leave) {
	case 'N': case 'n': 
		return 1;
		break;
	default: 
		return 0;
		break;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Игра 'Быки и коровы'. Угадай четырехзначное число!\n";
	for (int i = 0, exit=0; exit==0; ++i)
	{
		srand(time(0)*(i+1)+i); //рандом
		vector<int> game = v_generator();
		/*for (int d : game) cout << d;*/
		
		cout << "\nКомпьютер загадал число.\n";

		int num;
		for (bool win = false; win == false; )
		{
			cin >> num;
			int num_check = log10(num) + 1; //ПРОБЛЕМА: если число начинается с 0, то компьютер его не принимает. (временно решена: компьютер не может загадать число, начинающееся с 0)
			if (num_check == 4) win = the_game(game, num);
			else cerr << "Тут не четырехзначное число!\n\n";

		}
		cout << "Играть еще? (Y/N)\n";
		char leave = 'b';
		cin >> leave;
		exit = get_out(leave);
	}
	return 0;
}
