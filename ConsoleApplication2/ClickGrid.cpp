#include "ClickGrid.h"

ClickGrid::ClickGrid(int size, sf::Vector2f drawPos) : m_size(size), m_drawPos(drawPos), m_pixelArray(size*size, 0), m_squares(size*size, NULL) {
	m_background.setFillColor(sf::Color(128, 128, 128));
	m_background.setPosition(m_drawPos);
	m_background.setSize(sf::Vector2f(110*m_size + 10, 110 * m_size + 10));

	for (int i = 0; i < m_size*m_size; i++) {
		m_squares[i] = new sf::RectangleShape(sf::Vector2f(100, 100));
		m_squares[i]->setPosition(sf::Vector2f(m_drawPos.x + 10 + (i%m_size)*110, m_drawPos.y + 10 + (i/m_size) * 110));
		std::cout << "x: " << m_drawPos.x + 10 + (i%m_size) * 110 << " y: " << m_drawPos.y + 10 + (i/m_size) * 110 << std::endl;
	}
}

ClickGrid::~ClickGrid() {
	for (int i = 0; i < m_size*m_size; i++) {
		delete m_squares[i];
	}
}

void ClickGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_background, states);

	for (int i = 0; i < m_size*m_size; i++) {
		target.draw(*m_squares[i], states);
	}
}