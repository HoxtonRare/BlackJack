#include "BlackJack.h"

void Card::Flip()
{
	pos = !pos;
}
int Card::getValue() const
{
	return this->cardValue;
}
bool Card::getPos() const
{
	return this->pos;
}
char Card::getSuit() const
{
	switch (this->cardSuit)
	{
	case Clubs:return static_cast<char>(5); break;
	case Diamonds:return static_cast<char>(4); break;
	case Hearts:return static_cast<char>(3); break;
	case Spades:return static_cast<char>(6); break;
	}
}
Card::Card(value cValue, suit cSuit, bool ps) : cardValue(cValue), cardSuit(cSuit), pos(ps) {}

void Hand::add(Card* card)
{
	myCards.push_back(card);
}
void Hand::clear()
{
	myCards.clear();
	myCards.shrink_to_fit();
}
int Hand::getValue() const
{
	int value = 0;
	bool ace = false;
	for (int i = 0; i < myCards.size(); i++)
	{
		if (myCards[i]->getValue() == Card::Ace)
		{
			ace = true;
		}

		else if (myCards[i]->getValue() == Card::Jack || myCards[i]->getValue() == Card::Queen || myCards[i]->getValue() == Card::King)
		{
			value += 10;
		}

		else
		{
			value += myCards[i]->getValue();
		}
	}
	if (ace && value <= 11)
	{
		value += 10;
	}
	return value;
}
vector<Card*> Hand::GetCards() const
{
	return myCards;
}

GenericPlayer::GenericPlayer(string pName) : name(pName) {}
bool GenericPlayer::isBoosted()
{
	if (this->getValue() > 21)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GenericPlayer::Bust()
{
	cout << "У игрока " << name << " перебор" << endl;
}
string GenericPlayer::GetName() const
{
	return name;
}

ostream& operator << (ostream& os, const Card& card)
{
	if (card.getPos() == false)
	{
		return os << "XX";
	}
	else
	{
		switch (card.getValue())
		{
		case card.Ace: return os << 'A' << card.getSuit(); break;
		case card.Jack: return os << 'J' << card.getSuit(); break;
		case card.Queen: return os << 'Q' << card.getSuit(); break;
		case card.King: return os << 'K' << card.getSuit(); break;
		default: return os << card.getValue() << card.getSuit();
		}
	}
}

ostream& operator << (ostream& os, const GenericPlayer& gp)
{
	os << gp.GetName() << " || ";
	for (size_t k = 0; k < gp.GetCards().size(); ++k)
	{
		os << *gp.GetCards()[k];
	}
	return os;
}

Player::Player(string pname) : GenericPlayer(pname) {}
bool Player::IsHitting() const {
	if (GenericPlayer::getValue() > 21)
	{
		return false;
	}
	else
	{
		char ans;
		cout << "\n" << name << " нужна ли ещё одна карта?(Y/N)" << endl;
		bool corrAns = true;
		while (corrAns)
		{
			cin >> ans;
			if (ans == 'Y' || ans == 'y')
			{
				corrAns = false;
				return true;
			}
			else if (ans == 'N' || ans == 'n')
			{
				corrAns = false;
				return false;
			}
			else
			{
				cout << "Некорректный ответ. Пожалуйста выберите (Y/N)" << endl;
			}
		}
		cout << endl;
	}
}
void Player::Win() const
{
	cout << "Игрок " << name << " выиграл!" << endl;
}
void Player::Lose() const
{
	cout << "Игрок " << name << " проиграл!" << endl;
}
void Player::Push() const
{
	cout << "Игрок " << name << " сыграл вничью" << endl;
}

House::House() : GenericPlayer("Dealer") {}
bool House::IsHitting() const
{
	if (this->getValue() < 16)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void House::FlipFirstCard()
{
	myCards[0]->Flip();
}

Deck::Deck()
{
	myCards.reserve(52);
	Populate();
}
Deck::~Deck()
{
	myCards.clear();
	myCards.shrink_to_fit();
}

void Deck::Populate()
{
	clear();
	for (int i = Card::Hearts; i <= Card::Clubs; ++i)
	{
		for (int j = Card::Ace; j <= Card::King; ++j)
		{
			add(new Card(static_cast<Card::value> (j), static_cast<Card::suit> (i), true));
		}
	}
};

void Deck::Shuffle()
{
	srand(time(NULL));
	int temp, index;
	for (int i = 0; i < myCards.size(); ++i)
	{
		for (int j = 0; j < myCards.size(); j++)
		{
			swap(myCards.at(i), myCards.at(rand() % myCards.size()));
		}
	}
}

void Deck::Deal(Hand& hand)
{
	if (!myCards.empty())
	{
		hand.add(myCards.back());
		myCards.pop_back();
	}
	else
	{
		cout << "Карты закончились";
	}
}

void Deck::AddltionalCards(GenericPlayer& generlcPlayer)
{
	while (generlcPlayer.IsHitting())
	{
		Deal(generlcPlayer);
		cout << generlcPlayer << " - " << generlcPlayer.getValue();
	}
}

Game::Game(vector<string>& names)
{
	for (int i = 0; i < names.size(); ++i)
	{
		players.push_back(names.at(i));
	}
	deck.Shuffle();
}
Game::~Game()
{
	players.clear();
	players.shrink_to_fit();
}

void Game::printTable()
{
	system("cls");
	cout << "        ДОБРО ПОЖАЛОВАТЬ В BLACKJACK\n\n";
	cout << house << " || ";
	if (house.GetCards().at(0)->getPos())
	{
		if (house.isBoosted())
		{
			house.Bust();
		}
		else
		{
			cout << house.getValue();
		}
	}
	cout << endl;
	for (int i = 0; i < players.size(); ++i)
	{
		cout << players.at(i) << " || " << players.at(i).getValue() << endl;
		if (players.at(i).GetCards().at(0)->getPos())
		{
			if (players.at(i).isBoosted())
			{
				players.at(i).Bust();
			}
		}
	}
	cout << endl;
}

void Game::Play()
{
	for (int i = 0; i < players.size(); ++i)
	{
		deck.Deal(players.at(i));
		deck.Deal(players.at(i));
	}
	deck.Deal(house);
	deck.Deal(house);
	house.FlipFirstCard();

	printTable();

	for (int i = 0; i < players.size(); ++i)
	{
		deck.AddltionalCards(players.at(i));
		printTable();

	}
	house.FlipFirstCard();
	printTable();
	deck.AddltionalCards(house);
	printTable();

	for (int i = 0; i < players.size(); ++i)
	{
		if (((house.getValue() > 21) || (house.getValue() < players.at(i).getValue())) && (players.at(i).getValue() < 22))
		{
			cout << endl;
			players.at(i).Win();
		}
		else if ((house.getValue() == players.at(i).getValue()) && (players.at(i).getValue() < 22))
		{
			cout << endl;
			players.at(i).Push();
		}
		else
		{
			cout << endl;
			players.at(i).Lose();
		}
	}
	house.clear();
	for (int i = 0; i < players.size(); ++i)
	{
		players.at(i).clear();
	}
}

void Game::RenewDeck()
{
	deck.Populate();
	deck.Shuffle();
}

int checkNumber()
{
	int num;
	cout << "Введите число игроков(1-4): " << endl;
	while (!(cin >> num) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Некорректное число. Попробуйте ещё раз" << endl;
	}
	while (num < 1 || num > 4)
	{
		cout << "Некорректное число. Попробуйте ещё раз" << endl;
		cin >> num;
	}
	return num;
}