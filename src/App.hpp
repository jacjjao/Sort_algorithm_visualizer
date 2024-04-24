#pragma once
#ifndef APP_HPP
#define APP_HPP

#include "Common.hpp"
#include "Algorithm.hpp"
#include "Window.hpp"
#include <vector>


class App
{
private:
	State			  m_currentState = State::DO_NOTHING;

	const size_t      WINDOW_WIDTH = 2000;
	const size_t      WINDOW_HEIGHT = 1000;
	const sf::String  WINDOW_TITLE = "Sort Algorithm";

	const size_t	  MAX_DATA_SIZE = 500;

	size_t			  m_current_data_size = 200;

	std::vector<Data> m_data;
	
	Algorithm		  m_algorithm;

	Window			  m_window;

public:
	App();

	void run();
};


#endif