#include "ClickGrid.h"

ClickGrid::ClickGrid(int squareSize, int numSquares, sf::Vector2f drawPos):
	m_numSquares(numSquares), m_squareSize(squareSize), m_drawPos(drawPos), m_pixelArray(numSquares*numSquares, 0), m_squares(numSquares*numSquares, NULL) {

	std::cout << "Gap size in pixels: " << m_squareSize*.1 << "\n";

	m_background.setFillColor(sf::Color(128, 128, 128));
	m_background.setPosition(m_drawPos);
	m_background.setSize(sf::Vector2f(m_squareSize * (1.1* m_numSquares + .1), m_squareSize*(1.1 * m_numSquares + .1)));

	for (int i = 0; i < m_numSquares*m_numSquares; i++) {
		m_squares[i] = new sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));
		m_squares[i]->setPosition(sf::Vector2f(m_drawPos.x + .1*m_squareSize + (i%m_numSquares) * 1.1*m_squareSize, m_drawPos.y + .1*m_squareSize + (i / m_numSquares) * 1.1*m_squareSize));
	}
}

ClickGrid::ClickGrid(int numSquares, sf::Vector2f drawPos) : m_numSquares(numSquares), m_squareSize(100), m_drawPos(drawPos), m_pixelArray(numSquares*numSquares, 0), m_squares(numSquares*numSquares, NULL) {
	m_background.setFillColor(sf::Color(128, 128, 128));
	m_background.setPosition(m_drawPos);
	m_background.setSize(sf::Vector2f(110*m_numSquares + 10, 110 * m_numSquares + 10));

	for (int i = 0; i < m_numSquares*m_numSquares; i++) {
		m_squares[i] = new sf::RectangleShape(sf::Vector2f(100, 100));
		m_squares[i]->setPosition(sf::Vector2f(m_drawPos.x + 10 + (i%m_numSquares)*110, m_drawPos.y + 10 + (i/m_numSquares) * 110));
		std::cout << "x: " << m_drawPos.x + 10 + (i%m_numSquares) * 110 << " y: " << m_drawPos.y + 10 + (i/m_numSquares) * 110 << std::endl;
	}
}

ClickGrid::ClickGrid(int squareSize, int numSquares, sf::Vector2f drawPos, int):
	m_numSquares(numSquares), m_squareSize(squareSize), m_drawPos(drawPos), m_pixelArray(numSquares*numSquares, 0), m_squares(numSquares*numSquares, NULL), m_grayscale(1) {

	std::cout << "Gap size in pixels: " << m_squareSize*.1 << "\n";

	m_background.setFillColor(sf::Color(128, 128, 128));
	m_background.setPosition(m_drawPos);
	m_background.setSize(sf::Vector2f(m_squareSize * (1.1* m_numSquares + .1), m_squareSize*(1.1 * m_numSquares + .1)));

	for (int i = 0; i < m_numSquares*m_numSquares; i++) {
		m_squares[i] = new sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));
		m_squares[i]->setPosition(sf::Vector2f(m_drawPos.x + .1*m_squareSize + (i%m_numSquares) * 1.1*m_squareSize, m_drawPos.y + .1*m_squareSize + (i / m_numSquares) * 1.1*m_squareSize));
	}

}

ClickGrid::~ClickGrid() {
	for (int i = 0; i < m_numSquares*m_numSquares; i++) {
		delete m_squares[i];
	}
}

void ClickGrid::flipSquare(std::array<int, 2> square) {
	if (m_pixelArray[square[0] + m_numSquares*square[1]]) {
		m_squares[square[0] + m_numSquares*square[1]]->setFillColor(sf::Color::White);
		m_pixelArray[square[0] + m_numSquares*square[1]] = 0;
	}
	else {
		if (m_grayscale) {
			m_squares[square[0] + m_numSquares*square[1]]->setFillColor(sf::Color::Black);
			m_pixelArray[square[0] + m_numSquares*square[1]] = 255;
		}
		else {
			m_squares[square[0] + m_numSquares*square[1]]->setFillColor(sf::Color::Black);
			m_pixelArray[square[0] + m_numSquares*square[1]] = 1;
		}
	}
}

void ClickGrid::dragGrid(int clickX, int clickY) {

}

void ClickGrid::makeWaves() {
	int distances[] = {m_numSquares - 1 - m_lastSquare[0], m_lastSquare[0], m_numSquares - 1 - m_lastSquare[1], m_lastSquare[1]};

	int iterations = *std::max_element(distances, distances + 4);

	m_timer.restart();
	int i = 1;

	while(i <= iterations) {
		if (m_timer.getElapsedTime().asSeconds() > 1) {
			m_timer.restart();
			flipRing(i, m_lastSquare[0], m_lastSquare[1]);
			i++;
		}
	}
}

void ClickGrid::flipRing(int num, int x, int y) {
	for (int i = 0; i < 8 * num; i++) {
		if (i < 2 * num) {
			if (y - num >= 0 && x - num + i >= 0 && x - num + i < m_numSquares)
				flipSquare({x - num + i, y - num});
		}
		else if (i < 4 * num) {
			if (x + num < m_numSquares && y - num + i%(2*num) >= 0 && y - num + i % (2 * num) < m_numSquares)
				flipSquare({ x + num, y - num + i % (2 * num) });
		}
		else if (i < 6 * num) {
			if (y + num < m_numSquares && x + num - i%(2*num) >= 0 && x + num - i % (2 * num) < m_numSquares)
				flipSquare({ x + num - i % (2 * num), y + num });
		}
		else {
			if (x - num >= 0 && y + num - i%(2*num) >= 0  && y + num - i % (2 * num) < m_numSquares)
				flipSquare({ x - num, y + num - i % (2 * num) });
		}
	}
}

bool ClickGrid::livingSquare(int x, int y) {
	int livingSquares = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i || j) {
				int testX = x + i;
				int testY = y + j;
				if (0 <= testX && testX < m_numSquares && 0 <= testY && testY < m_numSquares) {
					if (m_pixelArray[testX + m_numSquares*testY])
						livingSquares++;
				}
			}
		}
	}
	if (m_pixelArray[x + m_numSquares*y]) {
		if (livingSquares == 2 || livingSquares == 3)
			return true;
	}
	else {
		if (livingSquares == 3)
			return true;
	}
	return false;
}

int ClickGrid::newColor(int x, int y) {
	int squareColor = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i || j) && (!i||!j)) {
				int testX = x + i;
				int testY = y + j;
				if (0 <= testX && testX < m_numSquares && 0 <= testY && testY < m_numSquares) {
					squareColor += m_pixelArray[testX + m_numSquares*testY];
				}
			}
		}
	}
	return (squareColor / 4);
}

bool ClickGrid::chooseSquare(int clickX, int clickY) {
	int relativeX = clickX - m_drawPos.x;
	int relativeY = clickY - m_drawPos.y;
	if ((0 <= relativeX && relativeX <= m_squareSize*(1.1 * m_numSquares + .1)) && (0 <= relativeY && relativeY <= m_squareSize*(1.1 * m_numSquares + .1))) {
		if (relativeX < m_squareSize*((relativeX / (int)(1.1*m_squareSize)) * 1.1 + .1) || relativeY < m_squareSize*((relativeY / (int)(1.1*m_squareSize)) * 1.1 + .1)) {
			std::cout << "selected between tiles at x: " << clickX << " y: " << clickY << std::endl;
			//drag grid
			return false;
		}
		else {
			std::cout << "selected square x: " << relativeX / (int)(1.1*m_squareSize) << " y: " << relativeY / (int)(1.1*m_squareSize) << std::endl;
			flipSquare({ relativeX / (int)(1.1*m_squareSize) , relativeY / (int)(1.1*m_squareSize) });
			m_lastSquare = { relativeX / (int)(1.1*m_squareSize) , relativeY / (int)(1.1*m_squareSize) };
			return true;
		}
	}
	else {
		std::cout << "selected outside grid" << std::endl;
		//m_waving = !m_waving;
		m_GOL = !m_GOL;
		return false;
	}
}

void ClickGrid::update() {
	/*if (m_waving && m_timer.getElapsedTime().asSeconds() > .1) {
		flipRing(2, m_lastSquare[0], m_lastSquare[1]);
		m_timer.restart();
	}*/
	if (m_GOL && m_timer.getElapsedTime().asSeconds() > .016) {
		std::vector<int> buffer = { 0 };
		buffer.resize(m_numSquares*m_numSquares, 0);
		if (!m_grayscale) {
			for (int i = 0; i < m_numSquares*m_numSquares; i++) {
				if (livingSquare(i%m_numSquares, i / m_numSquares)) {
					m_squares[i]->setFillColor(sf::Color::Black);
					buffer[i] = 1;
				}
				else {
					m_squares[i]->setFillColor(sf::Color::White);
					buffer[i] = 0;
				}
			}
		}
		else {
			for (int i = 0; i < m_numSquares*m_numSquares; i++) {
				int colorChange = newColor(i%m_numSquares, i / m_numSquares);
				if (colorChange) {
					m_squares[i]->setFillColor(sf::Color(255-colorChange, 255 - colorChange, 255 - colorChange));
					buffer[i] = colorChange;
				}
				else {
					m_squares[i]->setFillColor(sf::Color::White);
					buffer[i] = colorChange;
				}
				
 			}
		}
		m_pixelArray = buffer;
		m_timer.restart();
	}
}

void ClickGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_background, states);

	for (int i = 0; i < m_numSquares*m_numSquares; i++) {
		target.draw(*m_squares[i], states);
	}
}