#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP


#include "Common.hpp"
#include <SFML/Graphics.hpp>
#include <vector>


class Window : public sf::RenderWindow
{
private:
	sf::Clock m_timer;
	sf::Clock m_deltaClock;

	int       m_fps = 0;
	int       m_temp_size;

	State     m_state;
	State*    pState;

	size_t*   pDataSize;

	bool      m_running = true;
	bool      gui_enabled = true;

	void draw_gui();

	void draw_data(std::vector<Data>&);

public:
	using sf::RenderWindow::RenderWindow;

	void setDataSize(size_t&);
	void setState(State&);

	void update(std::vector<Data>&);

	void idle(unsigned, std::vector<Data>&);

};


#endif