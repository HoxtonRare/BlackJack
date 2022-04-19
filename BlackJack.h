#pragma once
#ifndef  BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

class Card {
public:
	enum suit {
		Hearts,
		Spades,
		Diamonds,
		Clubs
	};
	enum value {
		Ace,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King
	};
	bool pos = false;

	void Flip();

	int getValue() const;

	bool getPos() const;

	char getSuit() const;

	Card(value cValue, suit cSuit, bool ps);
protected:
	suit cardSuit;
	value cardValue;
};

class Hand {
protected:
	vector<Card*>myCards;
public:
	void add(Card* card);

	void clear();

	int getValue() const;
	
	bool ace = false;

	vector<Card*> GetCards() const;
};

class GenericPlayer : public Hand {
protected:
	string name;
public:
	GenericPlayer(string pName);
	virtual bool IsHitting() const = 0;
	bool isBoosted();

	void Bust();

	string GetName() const;
};

class Player : public GenericPlayer {
public:
	Player(string pname);

	virtual bool IsHitting() const;

	void Win() const;

	void Lose() const;

	void Push() const;
};

class House : public GenericPlayer {
public:
	House();

	virtual bool IsHitting() const;

	void FlipFirstCard();
};

class Deck : public Hand
{
public:
	Deck();

	~Deck();

	void Populate();

	void Shuffle();

	void Deal(Hand& hand);

	void AddltionalCards(GenericPlayer& generlcPlayer);
};

class Game
{
private:
	Deck deck;
	House house;
	vector<Player> players;
public:
	Game(vector<string>& names);

	~Game();

	void printTable();

	void Play();
	
	void RenewDeck();

};

int checkNumber();

#endif // ! BLACKJACK_H