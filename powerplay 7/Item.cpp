#include <iostream>
#include <memory>
#include <map>
#include "Item.h"

Item::Item(Type classification, int bonusValue) : classification(classification), bonusValue(bonusValue)
{
}

Item::Type Item::getClassification() const
{
	return classification;
}

int Item::getBonusValue() const
{
	return bonusValue;
}

std::ostream& operator<<(std::ostream& o, const Item::Type& classification) // changed? 
{
	switch (classification)
	{
	case Item::Type::armor:
		o << "armor";
		break;
	case Item::Type::shield:
		o << "shield";
		break;
	case Item::Type::sword:
		o << "sword";
		break;
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, const Item& item)
{
	o <<  item.getClassification();		// changed? idk. who knows what to place in the output? 
	return o;
}

std::ostream& operator<< (std::ostream& o, const std::map<Item::Type, std::unique_ptr<Item>>& src)
{
	for (const auto& item : src)
	{
		o << "  " << *item.second << std::endl;
	};
	return o;
}

bool operator<(const Item& srcL, const Item& srcR)
{
	return srcL.getBonusValue() < srcR.getBonusValue();
}

int& operator+=(int& srcL, const Item& srcR)
{
	srcL += srcR.getBonusValue();
	return srcL;
}

int operator+(const Item& srcL, const Item& srcR)
{
	return srcL.getBonusValue() + srcR.getBonusValue();
}
