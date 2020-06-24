#include <random>
#include <iostream>

#include "Monster.h"
#include "Object.h"

std::random_device Object::seed;
std::default_random_engine Object::engine(seed());

Object::Object(Type name, int strength, int health, int level) : name{ name }, strength{ strength }, health{ health }, level{ level }
{
}



bool Object::isDead()
{
	if (health <= 0) {return true;}
	else {return false;}
}

Object::Type Object::getName() const
{
	return name;
}

int Object::getLevel() const
{
	return level;
}

int Object::getHealth() const
{
	return health;
}

std::ostream& operator<<(std::ostream& o, const Object& src)
{
	o << "L:" << src.getLevel() << " ";
	switch (src.getName())
	{
	case Object::Type::player:
		std::cout << "Player";
		break;
	case Object::Type::slime:
		std::cout << "Slime";
		break;
	case Object::Type::orc:
		std::cout << "Orc";
		break;
	case Object::Type::sprite:
		std::cout << "Sprite";
		break;
	case Object::Type::dragon:
		std::cout << "Dragon";
		break;
	}
	o << " h:" << src.getHealth();
	return o;
}

//int Object::damageDone(int modification) const
//{
//	int potentialDamage{ strength + modification };
//	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);
//	std::cout << *this << " deals ";
//	return std::max(1, (int)damageDealt(engine));
//}

int Object::damageDone(int modification) const		
{
	int potentialDamage{ strength + modification };
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	int damage = std::max(1, (int)damageDealt(engine));
	//std::cout << *this << " deals " << damage  << " damage!" << std::endl;
	return damage;

}
//int Object::damageTaken(int damageDone, int AC)
//{
//	return this->health -= (damageDone + AC);
//}

int Object::damageTaken(int damageDone, int AC)
{
	//std::normal_distribution<double> defense(AC, 1.0 / level);
	//damageDone = std::max(0, damageDone - (int)defense(engine));
	//damageDone = 1;				// damage is always 1...
	//std::cout << damageDone << " damage to ";
	//std::cout << *this << "!!!" << std::endl;
	//health -= (damageDone + AC);
	//return health;
	std::cout << *this << " takes " << damageDone + AC << " damage!" << std::endl;
	return this->health -= (damageDone + AC);
}