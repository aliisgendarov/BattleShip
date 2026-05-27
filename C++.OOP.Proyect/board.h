#pragma once

enum CellState
{
	Empty,
	ShipCell,
	Hit,
	Miss,
	Destroyed
};

class Board
{
private:
	static const int WIDTH = 10;
	static const int HEIGHT = 10;

	ushort _oneCellCount = 3;
	ushort _twoCellCount = 2;
	ushort _threeCellCount = 1;

	CellState _board[HEIGHT][WIDTH]{};
	vector<Ship> _ships;

public:
	Board()
	{
		clearBoard();
	}

	int getWidth() const { return WIDTH; }
	int getHeight() const { return HEIGHT; }
	ushort getOneCellCount() const { return _oneCellCount; }
	ushort getTwoCellCount() const { return _twoCellCount; }
	ushort getThreeCellCount() const { return _threeCellCount; }

	bool isInside(int x, int y) const
	{
		return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
	}

	bool moveChek(Ship& ship, int xx = 0, int yy = 0)
	{
		vector<Position> cells = ship.getCells();

		for (const auto& cell : cells)
		{
			if (!isInside(cell.x + xx, cell.y + yy))
				return false;
		}

		return true;
	}

	bool haveShipToPut()
	{
		return _oneCellCount != 0 || _twoCellCount != 0 || _threeCellCount != 0;
	}

	bool isShipCountFinished(const Ship& ship) const
	{
		if (ship.getSize() == one)
			return _oneCellCount == 0;

		if (ship.getSize() == two)
			return _twoCellCount == 0;

		if (ship.getSize() == three)
			return _threeCellCount == 0;

		return true;
	}

	bool intoBoard(Ship& ship)
	{
		vector<Position> cells = ship.getCells();

		for (const auto& cell : cells)
		{
			if (!isInside(cell.x, cell.y))
				return false;
		}

		return true;
	}

	bool rotateCheckAndDone(Ship& ship)
	{
		ship.changeDirection();

		bool check = intoBoard(ship);

		if (check)
			return true;

		ship.changeDirection();

		return false;
	}

	bool canPlaceShip(const Ship& ship) const
	{
		vector<Position> cells = ship.getCells();

		for (const auto& cell : cells)
		{
			if (!isInside(cell.x, cell.y))
				return false;

			for (int yy = cell.y - 1; yy <= cell.y + 1; yy++)
			{
				for (int xx = cell.x - 1; xx <= cell.x + 1; xx++)
				{
					if (isInside(xx, yy))
					{
						if (_board[yy][xx] == ShipCell)
							return false;
					}
				}
			}
		}

		return true;
	}

	bool placeShip(const Ship& ship)
	{
		if (!canPlaceShip(ship) || 
			(ship.getSize() == 1 && _oneCellCount == 0) || (ship.getSize() == 2 && _twoCellCount == 0) ||
			ship.getSize() == 3 && _threeCellCount == 0)
			return false;

		vector<Position> cells = ship.getCells();

		for (const auto& cell : cells)
		{
			_board[cell.y][cell.x] = ShipCell;	
		}

		ship.getSize() == 1 ? _oneCellCount-- : ship.getSize() == 2 ? _twoCellCount-- : _threeCellCount--;

		_ships.push_back(ship);

		return true;
	}

	void draw(int cursorX = -1, int cursorY = -1, const Ship* previewShip = nullptr) const
	{
		cout << (char)201;


		for (int i = 0; i < WIDTH * 2; i++)
			cout << (char)205;

		cout << (char)187 << endl;

		vector<Position> previewCells;

		if (previewShip != nullptr)
			previewCells = previewShip->getCells();

		for (int y = 0; y < HEIGHT; y++)
		{
			cout << (char)186;

			for (int x = 0; x < WIDTH; x++)
			{
				bool isPreview = false;

				for (const auto& p : previewCells)
				{
					if (p.x == x && p.y == y)
					{
						isPreview = true;
						break;
					}
				}


				if (isPreview)
				{
					previewShip->getSize() == 1 ? cout << "\033[32mOO" : previewShip->getSize() == 2 ? cout << "\033[32m00"
						: cout << "\033[32mOO";
					
					cout << "\033[0m";
					continue;
				}

				switch (_board[y][x])
				{
				case Empty:
					cout << "\033[90m" << (char)Cell << (char)Cell;
					break;

				case ShipCell:
					cout << "\033[97m" << "OO";
					break;

				case Hit:
					cout << "\033[31m" << "H";
					break;

				case Miss:
					cout << "\033[34m" << "M";
					break;

				case Destroyed:
					cout << "\033[32m" << "A";
					break;
				}

				cout << "\033[0m";
			}

			cout << (char)186 << endl;
		}

		cout << (char)200;

		for (int i = 0; i < WIDTH * 2; i++)
			cout << (char)205;

		cout << (char)188 << endl;
	}

	void autoPlaceShip(ShipSize size)
	{
		while (true)
		{
			Ship ship(size, rand() % 2 == 0 ? Horizontal : Vertical, { rand() % WIDTH, rand() % HEIGHT });

			if (placeShip(ship))
				break;
		}
	}

	void placeShipsAutomatically()
	{
		while (_oneCellCount > 0)
			autoPlaceShip(one);

		while (_twoCellCount > 0)
			autoPlaceShip(two);

		while (_threeCellCount > 0)
			autoPlaceShip(three);
	}

	Ship* findShipAtPosition(int x, int y)
	{
		for (auto& ship : _ships)
		{
			vector<Position> cells = ship.getCells();

			for (const auto& cell : cells)
			{
				if (cell.x == x && cell.y == y)
					return &ship;
			}
		}

		return nullptr;
	}

	bool attack(int x, int y)
	{
		if (!isInside(x, y))
			return false;

		if (_board[y][x] == ShipCell)
		{
			Ship* ship = findShipAtPosition(x, y);

			if (ship != nullptr)
			{
				ship->hit();

				if (ship->isDestroyed())
				{
					vector<Position> cells = ship->getCells();

					for (const auto& cell : cells)
					{
						_board[cell.y][cell.x] = Destroyed;
					}
				}
				else
				{
					_board[y][x] = Hit;
				}
			}

			return true;
		}

		return false;
	}

	void clearBoard()
	{
		_ships.clear();

		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				_board[y][x] = Empty;
			}
		}
	}

	int aliveShipsCount() const
	{
		int count = 0;

		for (const auto& ship : _ships)
		{
			if (!ship.isDestroyed())
				count++;
		}

		return count;
	}
};