#include "App.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>


App::App()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar)
{
	m_algorithm.setWindow(m_window);

	m_data.reserve(MAX_DATA_SIZE);
	for (size_t i = 1; i <= MAX_DATA_SIZE; i++)
	{
		m_data.emplace_back(i, 250, 250, 250);
	}

	m_window.setDataSize(m_current_data_size);
	m_window.setState(m_currentState);
}

void App::run()
{
	ImGui::SFML::Init(m_window);

	while (m_window.isOpen())
	{
		m_window.update(m_data);

		if (m_currentState != State::DO_NOTHING)
		{
			m_algorithm.setDataSize(m_current_data_size);

			make_color_white(m_data, m_current_data_size);

			m_algorithm.shuffle(m_data);
			m_window.idle(1000, m_data);

			switch (m_currentState)
			{
			case State::ALL:
				m_algorithm.execute_all_algorithm(m_data);
				break;

			case State::BUBBLE_SORT:
				m_algorithm.bubble_sort(m_data);
				break;

			case State::SELECTION_SORT:
				m_algorithm.selection_sort(m_data);
				break;

			case State::INSERTION_SORT:
				m_algorithm.insertion_sort(m_data);
				break;

			case State::MERGE_SORT:
				m_algorithm.merge_sort(m_data);
				break;

			case State::QUICK_SORT:
				m_algorithm.quick_sort(m_data);
				break;

			case State::HEAP_SORT:
				m_algorithm.heap_sort(m_data);
				break;
			}

			m_currentState = State::DO_NOTHING;

		}
	}

	ImGui::SFML::Shutdown();
}
