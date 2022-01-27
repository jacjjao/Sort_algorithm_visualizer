#include "Window.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <string>


void Window::draw_gui()
{
	ImGui::Begin("Settings");

	ImGui::BeginDisabled(!gui_enabled);

	ImGui::Text("Array size: "); ImGui::SameLine();
	ImGui::RadioButton("50", &m_temp_size, 50); ImGui::SameLine();
	ImGui::RadioButton("100", &m_temp_size, 100); ImGui::SameLine();
	ImGui::RadioButton("200", &m_temp_size, 200); ImGui::SameLine();
	ImGui::RadioButton("250", &m_temp_size, 250); ImGui::SameLine();
	ImGui::RadioButton("500", &m_temp_size, 500); //ImGui::SameLine();
	//ImGui::RadioButton("1000", &m_temp_size, 1000);

	static std::vector<std::string> items = { "All", "Bubble sort", "Selection sort", 
											  "Insertion sort", "Merge sort", "Quick sort", 
		                                      "Heap sort" };
	static const size_t	ITEMS_LEN = items.size();
	static size_t		selected_index = 0;
	static std::string	selected_item = items.at(selected_index);


	if (ImGui::BeginCombo("Algorithm", selected_item.c_str()))
	{
		for (int i = 0; i < ITEMS_LEN; i++)
		{
			bool is_selected = (selected_item == items.at(i));

			if (ImGui::Selectable(items.at(i).c_str(), is_selected))
			{
				selected_item = items.at(i);
				selected_index = i;
			}	

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		switch (selected_index)
		{
		case 0:
			m_state = State::ALL;
			break;

		case 1:
			m_state = State::BUBBLE_SORT;
			break;

		case 2:
			m_state = State::SELECTION_SORT;
			break;

		case 3:
			m_state = State::INSERTION_SORT;
			break;

		case 4:
			m_state = State::MERGE_SORT;
			break;

		case 5:
			m_state = State::QUICK_SORT;
			break;

		case 6:
			m_state = State::HEAP_SORT;
			break;
		}

		ImGui::EndCombo();
	}

	if (ImGui::Button("Sort!"))
	{
		*pState = m_state;
		gui_enabled = false;
 	}

	ImGui::EndDisabled();

	ImGui::End();
}

void Window::setDataSize(size_t& dataSize)
{
	pDataSize   = &dataSize;
	m_temp_size = *pDataSize;
}

void Window::setState(State& state)
{
	pState = &state;
}

void Window::update(std::vector<Data>& data)
{
	sf::Event event;
	while (this->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			this->close();
			m_running = false;
			return;
		}
	}

	ImGui::SFML::Update(*this, m_deltaClock.restart());

	gui_enabled = (*pState == State::DO_NOTHING);

	draw_gui();

	this->clear(sf::Color(128, 128, 128));

	if (*pState == State::DO_NOTHING && m_temp_size != *pDataSize)
	{
		*pDataSize = static_cast<size_t>(m_temp_size);
		make_color_white(data, *pDataSize);
	}

	draw_data(data);

	ImGui::SFML::Render(*this);

	this->display();

	m_fps++;
	if (m_timer.getElapsedTime().asSeconds() >= 1.0f)
	{
		std::cout << "Fps: " << m_fps << std::endl;
		m_fps = 0;
		m_timer.restart();
	}
}

void Window::idle(unsigned duration, std::vector<Data>& data)
{
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() < static_cast<float>(duration) && m_running)
	{
		update(data);
	}
}

void Window::draw_data(std::vector<Data>& data)
{
	const size_t LEN = *pDataSize;

	sf::Vector2u size = this->getSize();

	float fWidth  = static_cast<float>(size.x);
	float fHeight = static_cast<float>(size.y);
	float fLen    = static_cast<float>(LEN);

	for (size_t i = 0; i < LEN; i++)
	{
		float width  = fWidth / fLen;
		float height = (fHeight / fLen) * static_cast<float>(data.at(i).val);

		sf::RectangleShape rect(sf::Vector2f(width, height));
		rect.setPosition(i * width, fHeight - height);

		rect.setFillColor(data.at(i).color);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-0.5f);

		this->draw(rect);
	}
}
