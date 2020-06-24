#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "Object.h"
#include "Item.h"

class Monster;
class Player : public Object
{
public:
	Player();

	void levelUp();
	int getLevel() const;
	int getSP() const;

	const std::map<Item::Type, std::unique_ptr<Item>>& getInventory() const; // CHANGED.

	void heal();

	int attack() const override;
	void defend(int damage) override;
	void update(Player* player, std::vector<std::unique_ptr<Monster>>& monster) override;


private:
	std::map<Item::Type, std::unique_ptr<Item>> inventory;
	int SP{ 0 };
};
std::ostream& operator<< (std::ostream& o, const Player& src);
//std::ostream& operator<< (std::ostream& o, std::map<Item::Type, std::unique_ptr<Item>>& src); //this is already defined in Item.cpp
#endif // !PLAYER_H