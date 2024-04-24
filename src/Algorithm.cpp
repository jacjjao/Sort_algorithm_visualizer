#include "Algorithm.hpp"
#include <random>
#include <iostream>
#include <cmath>


void Algorithm::setWindow(Window& window)
{
	this->pWindow = &window;
}

void Algorithm::setDataSize(size_t& size)
{
	m_data_size = size;
}

void Algorithm::execute_all_algorithm(std::vector<Data>& data)
{
	bubble_sort(data);

	make_color_white(data, m_data_size);
	shuffle(data);
	pWindow->idle(1000, data);

	selection_sort(data);

	make_color_white(data, m_data_size);
	shuffle(data);
	pWindow->idle(1000, data);

	insertion_sort(data);

	make_color_white(data, m_data_size);
	shuffle(data);
	pWindow->idle(1000, data);

	merge_sort(data);

	make_color_white(data, m_data_size);
	shuffle(data);
	pWindow->idle(1000, data);

	quick_sort(data);

	make_color_white(data, m_data_size);
	shuffle(data);
	pWindow->idle(1000, data);
	
	heap_sort(data);
}

void Algorithm::shuffle(std::vector<Data>& data)
{
	std::cout << "Shuffling..." << std::endl;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<size_t> dist(0, m_data_size - 1);

	for (size_t i = 0; i < m_data_size; i++)
	{
		std::swap(data.at(i), data.at(dist(mt)));

		pWindow->idle(SHUFFLE_DELAY, data);
	}
}

void Algorithm::color_fade(std::vector<Data>& data)
{
	for (size_t i = 0; i < m_data_size; i++)
	{
		sf::Color color(std::move(data.at(i).color));

		color.g = (color.g + DIFF > 255) ? 255 : color.g + DIFF;
		color.b = (color.b + DIFF > 255) ? 255 : color.b + DIFF;

		data.at(i).color = std::move(color);
	}
}

void Algorithm::finish(std::vector<Data>& data)
{
	make_color_white(data, m_data_size);

	pWindow->update(data);

	for (size_t i = 0; i < m_data_size; i++)
	{
		data.at(i).color = sf::Color::Green;

		pWindow->idle(3, data);
	}

	pWindow->idle(1000, data);
}

void Algorithm::bubble_sort(std::vector<Data>& data)
{
	std::cout << "Bubble sort" << std::endl;

	for (size_t i = m_data_size - 1; i > 0; i--)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (data.at(j).val > data.at(j + 1).val)
			{
				std::swap(data.at(j), data.at(j + 1));

				data.at(j).color = data.at(j + 1).color = sf::Color::Red;

				pWindow->idle(BUBBLE_DELAY, data);

				color_fade(data);				
			}	
		}
	}

	finish(data);
}

void Algorithm::selection_sort(std::vector<Data>& data)
{
	std::cout << "Selection sort" << std::endl;

	for (size_t i = 0; i < m_data_size - 1; i++)
	{
		size_t minPos = i;
		for (size_t j = i + 1; j < m_data_size; j++)
			if (data.at(j).val < data.at(minPos).val)
				minPos = j;

		std::swap(data.at(i), data.at(minPos));
		data.at(i).color = data.at(minPos).color = sf::Color::Red;

		pWindow->idle(SLECTION_DELAY, data);

		color_fade(data);
	}

	finish(data);
}

void Algorithm::insertion_sort(std::vector<Data>& data)
{
	std::cout << "Insertion sort" << std::endl;

	for (size_t i = 1; i < m_data_size; i++)
	{
		for (size_t j = i; j > 0; j--)
		{
			if (data.at(j).val < data.at(j - 1).val)
			{
				std::swap(data.at(j), data.at(j - 1));
				data.at(j).color = data.at(j - 1).color = sf::Color::Red;

				pWindow->idle(INSERTION_DELAY, data);

				color_fade(data);

				continue;
			}

			color_fade(data);
		}
	}

	finish(data);
}

void Algorithm::merge(std::vector<Data>& data, size_t l, size_t r)
{
	if (l < r)
	{
		size_t m = (l + r) / 2;
		merge(data, l, m);
		merge(data, m + 1, r);

		std::vector<int> left(m - l + 1), right(r - m);
		size_t len = std::max(m - l + 1, r - m + 1);

		for (size_t i = 0; i < len; i++)
		{
			if (i < left.size())
			{
				left.at(i) = data.at(l + i).val;
				data.at(l + i).color = sf::Color::Red;
			}
			if (i < right.size())
			{
				right.at(i) = data.at(m + i + 1).val;
				data.at(m + i + 1).color = sf::Color::Red;
			}
			pWindow->idle(MERGE_DELAY, data);
			color_fade(data);
		}
		size_t i = l;
		size_t leftIndex = 0, rightIndex = 0;
		size_t lLen = left.size(), rLen = right.size();

		while (leftIndex < lLen && rightIndex < rLen)
		{
			data.at(i).color = sf::Color::Red;
			if (left.at(leftIndex) < right.at(rightIndex))
			{
				data.at(i++).val = left.at(leftIndex++);
			}
			else
			{
				data.at(i++).val = right.at(rightIndex++);
			}
			pWindow->idle(MERGE_DELAY, data);
			color_fade(data);
		}
		while (leftIndex < lLen)
		{
			data.at(i).color = sf::Color::Red;
			data.at(i++).val = left.at(leftIndex++);
			pWindow->idle(MERGE_DELAY, data);
			color_fade(data);
		}
		while (rightIndex < rLen)
		{
			data.at(i).color = sf::Color::Red;
			data.at(i++).val = right.at(rightIndex++);
			pWindow->idle(MERGE_DELAY, data);
			color_fade(data);
		}
	}
}

void Algorithm::merge_sort(std::vector<Data>& data)
{
	std::cout << "Merge sort" << std::endl;

	merge(data, 0, m_data_size - 1);

	finish(data);
}

void Algorithm::quick(std::vector<Data>& data, size_t low, size_t high)
{
	if (low >= high) return;

	int pivot = data.at(high - 1).val;
	size_t j = low - 1;
	for (size_t i = low; i < high - 1; ++i)
	{
		if (data.at(i).val < pivot)
		{
			std::swap(data.at(i), data.at(++j));
			data.at(i).color = data.at(j).color = sf::Color::Red;
			pWindow->idle(QUICK_DELAY, data);
			color_fade(data);
		}
	}

	std::swap(data.at(high - 1), data.at(++j));
	data.at(high - 1).color = data.at(j).color = sf::Color::Red;
	pWindow->idle(QUICK_DELAY, data);
	color_fade(data);

	quick(data, low, j);
	quick(data, j + 1, high);
}

void Algorithm::quick_sort(std::vector<Data>& data)
{
	std::cout << "Quick sort" << std::endl;

	quick(data, 0, m_data_size);

	finish(data);
}

void Algorithm::heapify(std::vector<Data>& data, size_t n, size_t i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && data.at(l) > data.at(largest))
		largest = l;

	// If right child is larger than largest so far
	if (r < n && data.at(r) > data.at(largest))
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		std::swap(data.at(i), data.at(largest));

		data.at(i).color = data.at(largest).color = sf::Color::Red;
		pWindow->idle(HEAP_DELAY, data);
		color_fade(data);

		// Recursively heapify the affected sub-tree
		heapify(data, n, largest);
	}
}

void Algorithm::heap_sort(std::vector<Data>& data)
{
	std::cout << "Heap sort" << std::endl;

	// Build heap (rearrange array)
	for (int i = m_data_size / 2 - 1; i >= 0; i--)
		heapify(data, m_data_size, i);

	// One by one extract an element from heap
	for (int i = m_data_size - 1; i > 0; i--)
	{
		// Move current root to end
		std::swap(data.at(0), data.at(i));

		data.at(0).color = data.at(i).color = sf::Color::Red;

		pWindow->idle(HEAP_DELAY, data);
		color_fade(data);

		// call max heapify on the reduced heap
		heapify(data, i, 0);
	}

	finish(data);
}
