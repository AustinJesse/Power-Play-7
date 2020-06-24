#include <random>
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <map>

#include "Player.h"
#include "Monster.h"

Player::Player() :Object(Object::Type::player, 0, 1, 0)
{

}

void Player::levelUp()
{
	level++;
	std::normal_distribution<double> randomHealth(20.0 + level * 5, 5.0);
	health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + level, 1.0);
	strength += std::max(1, (int)randomStrength(engine));
	SP += std::max(1, (int)randomStrength(engine));


	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)level, (double)level / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };

	std::cout << "You found a " << found << "!!!!" << std::endl;
	if (
		auto haveOne{ inventory.find(found.getClassification()) };
		haveOne == inventory.end()
		|| *inventory[found.getClassification()] < found 
		) 
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		inventory[found.getClassification()] = std::make_unique<Item>(found.getClassification(), found.getBonusValue()); // FIXED. used make_unique
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

int Player::getLevel() const
{
	return level;
}

int Player::getSP() const
{
	return SP;
}

const std::map<Item::Type, std::unique_ptr<Item>>& Player::getInventory() const
{
	return inventory;
}

void Player::heal()
{
	if (SP >= 2)
	{
		std::normal_distribution<double> randomHeal(strength, 3.0);
		int  amountHealed{ std::max(1, (int)randomHeal(engine)) };

		SP -= 2;
		std::cout << *this << " is healed by " << amountHealed << "hp!" << std::endl;
		health += amountHealed;
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& o, const Player& src)
{
	o << (Object&)src << ", SP:" << src.getSP();
	return o;
}


int Player::attack() const 
{
	
	if (auto sword{ inventory.find(Item::Type::sword) }; sword != inventory.end())
	{
		return damageDone(sword->second->getBonusValue());
	}
	else
	{
		return damageDone(0); 
	}

}

void Player::defend(int damage) 
{
	//int total{ 0 };									// PLAYER 26 health
	//total = damageTaken(damage, this->strength);	// PLAYER 25 health
	//this->health = /*this->health - */total;				// player = 0 health
	//this->health -= total;
	damageTaken(damage, this->strength);
}
void Player::update(Player* player, std::vector<std::unique_ptr<Monster>>& monster) {
	std::cout << "Do you wish to (a)ttack or (h)eal? ";
	char command{ 'x' };
	std::cin >> command;
	switch (command)
	{
	case 'a':
	{
		std::cout << "Which Monster: ";
		int monsterNum{ 0 };
		std::cin >> monsterNum;
		if (monsterNum > 0 && monsterNum <= monster.size())
		{
			monster[monsterNum - 1]->defend(player->attack());
		}
		//playerAttack(player, monsters); // NOT MINE.
		break;
	}
	case 'h':
		player->heal();
		break;
	}
}