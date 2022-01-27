#include "Common.hpp"


Data::Data(const int w, const int x, const int y, const int z)
	: val(w), color(x, y ,z) {}

bool Data::operator>(const Data& d)
{
	return this->val > d.val;
}

bool Data::operator>=(const Data& d)
{
	return this->val >= d.val;
}

bool Data::operator<(const Data& d)
{
	return this->val < d.val;
}

bool Data::operator<=(const Data& d)
{
	return this->val <= d.val;
}

bool Data::operator!=(const Data& d)
{
	return this->val != d.val;
}

bool Data::operator==(const Data& d)
{
	return this->val == d.val;
}

void make_color_white(std::vector<Data>& data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		data.at(i).color = sf::Color::White;
}
