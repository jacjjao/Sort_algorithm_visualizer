#pragma once
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


#include "Common.hpp"
#include "Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>


class Algorithm
{
private:

	const int      DIFF = 25;

	const unsigned SHUFFLE_DELAY = 7;
	const unsigned BUBBLE_DELAY = 3;
	const unsigned SLECTION_DELAY = 50;
	const unsigned INSERTION_DELAY = 5;
	const unsigned MERGE_DELAY = 15; 
	const unsigned QUICK_DELAY = 15;
	const unsigned HEAP_DELAY = 15;
	const unsigned STD_SORT_DELAY = 15;

	size_t		   m_data_size = 200;

	Window*		   pWindow = nullptr;

	void color_fade(std::vector<Data>&);

	void finish(std::vector<Data>&);

	void merge(std::vector<Data>&, size_t, size_t);

	void quick(std::vector<Data>&, size_t, size_t);

	void heapify(std::vector<Data>&, size_t, size_t);

public:
	void setWindow(Window&);
	void setDataSize(size_t&);

	void execute_all_algorithm(std::vector<Data>&);
	void shuffle(std::vector<Data>&);
	void bubble_sort(std::vector<Data>&);
	void selection_sort(std::vector<Data>&);
	void insertion_sort(std::vector<Data>&);
	void merge_sort(std::vector<Data>&);
	void quick_sort(std::vector<Data>&);
	void heap_sort(std::vector<Data>&);
};

#endif