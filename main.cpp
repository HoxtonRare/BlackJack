#include "BlackJack.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	vector<string> names;
	int numPlayers;
	string name;
	char ans;
	bool retry = false;

	numPlayers = checkNumber();

	for (size_t k = 1; k <= numPlayers; ++k)
	{
		cout << "Введите имя " << k << " игрока: " << endl;
		cin >> name;
		names.push_back(name);
	}
	name.clear();
	name.shrink_to_fit();

	unique_ptr<Game> game(new Game(names));
	do
	{
		game->Play();

		cout << endl;

		cout << "Попробовать ещё раз?(Y/N)";

		bool corrAns = true;
		while (corrAns)
		{
			cin >> ans;
			if (ans == 'Y' || ans == 'y')
			{
				corrAns = false;
				retry = true;
			}
			else if (ans == 'N' || ans == 'n')
			{
				corrAns = false;
				retry = false;
			}
			else
			{
				cout << "Некорректный ответ. Пожалуйста выберите (Y/N)" << endl;
			}
		}

		game->RenewDeck();
	} while (retry == true);

	names.clear();
	names.shrink_to_fit();

	return 0;
}

