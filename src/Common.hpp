#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/Graphics/Color.hpp>
#include <vector>


enum class State {
	ALL, BUBBLE_SORT, SELECTION_SORT, 
	INSERTION_SORT, MERGE_SORT, QUICK_SORT, 
	HEAP_SORT, DO_NOTHING
};

struct Data {
	int val;
	sf::Color color;
	Data(const int, const int, const int, const int);
	bool operator>(const Data& d);
	bool operator>=(const Data& d);
	bool operator<(const Data& d);
	bool operator<=(const Data& d);
	bool operator!=(const Data& d);
	bool operator==(const Data& d);
};

void make_color_white(std::vector<Data>&, size_t);


#endif

