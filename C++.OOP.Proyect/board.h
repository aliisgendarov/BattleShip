#pragma once

enum CellState
{
	Empty,
	ShipCell,
	Hit,
	Miss,
	Destroyed
};

enum AttackResult
{
	AlreadyAttacked,
	Missed,
	Hitted,
	DestroyedShip
};

class Board
{
private:
	static const int WIDTH = 10;
	static const int HEIGHT = 10;

	ushort _oneCellCount = 4;
	ushort _twoCellCount = 3;
	ushort _threeCellCount = 2;

	CellState _board[HEIGHT][WIDTH]{};
	vector<Ship> _ships;

public:
	Board() { clearBoard(); }

	int getWidth() const { return WIDTH; }
	int getHeight() const { return HEIGHT; }
	ushort getOneCellCount() const { return _oneCellCount; }
	ushort getTwoCellCount() const { return _twoCellCount; }
	ushort getThreeCellCount() const { return _threeCellCount; }

	bool isInside(int x, int y) const
	{
		return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
	}

	bool moveCheck(const Ship& ship, int xx = 0, int yy = 0) const
	{
		for (const auto& cell : ship.getCells())
			if (!isInside(cell.x + xx, cell.y + yy))
				return false;

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
		for (const auto& cell : ship.getCells())
			if (!isInside(cell.x, cell.y))
				return false;

		return true;
	}

	void rotateCheckAndDone(Ship& ship)
	{
		ship.rotate();

		if (intoBoard(ship))
			return;

		ship.rotate();
	}

	CellState getCellState(int x, int y) const
	{
		if (!isInside(x, y))
			throw out_of_range("Invalid board coordinates!");

		return _board[y][x];
	}

	bool canPlaceShip(const Ship& ship) const // Ship qoyula biler yoxsa yox
	{
		vector<Position> cells = ship.getCells();

		for (const auto& cell : cells)
		{
			if (!isInside(cell.x, cell.y))
				return false;

			for (int yy = cell.y - 1; yy <= cell.y + 1; yy++) // ship e 1 cell yaxinliqda gemi qoymaq olmaz onun ucun yoxlma
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

	bool placeShip(const Ship& ship) // shipi elave etme
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

	string createTopBorder() const
	{
		string top;

		top += (char)201;

		for (int i = 0; i < WIDTH * 2; i++)
			top += (char)205;

		top += (char)187;

		return top;
	}

	string createBottomBorder() const
	{
		string bottom;

		bottom += (char)200;

		for (int i = 0; i < WIDTH * 2; i++)
			bottom += (char)205;

		bottom += (char)188;

		return bottom;
	}

	bool isPreviewCell(int x, int y, const vector<Position>& previewCells) const
	{
		for (const auto& p : previewCells)
			if (p.x == x && p.y == y)
				return true;

		return false;
	}

	bool isCursorPosition(int x, int y, int cursorX, int cursorY) const
	{
		return x == cursorX && y == cursorY;
	}

	string renderNormalCell(CellState state, bool hideShips) const
	{
		string cell;

		switch (state)
		{
		case Empty:
			cell += "\033[90m";
			cell += (char)Cell;
			cell += (char)Cell;
			cell += "\033[0m";

			break;
		case ShipCell:
			if (hideShips)
			{
				cell += "\033[90m";
				cell += (char)Cell;
				cell += (char)Cell;
				cell += "\033[0m";
			}
			else
				cell += "\033[97mOO\033[0m";

			break;
		case Hit:
			cell += "\033[34mH \033[0m";

			break;
		case Miss:
			cell += "\033[31mM \033[0m";

			break;
		case Destroyed:
			cell += "\033[32mA \033[0m";

			break;
		}

		return cell;
	}

	string renderCursorCell(CellState state, bool hideShips) const
	{
		string cell = "\033[43m";

		switch (state)
		{
		case Empty:
			cell += "  ";
			break;
		case ShipCell:
			if (hideShips)
				cell += "  ";
			else
				cell += "OO";

			break;
		case Hit:
			cell += "H ";
			break;
		case Miss:
			cell += "M ";
			break;
		case Destroyed:
			cell += "A ";
			break;
		}
		cell += "\033[0m";

		return cell;
	}

	string renderCell(int x, int y, int cursorX, int cursorY, const vector<Position>& previewCells, bool hideShips) const
	{
		if (isPreviewCell(x, y, previewCells))
			return "\033[32mOO\033[0m";

		bool isCursor = isCursorPosition(x, y, cursorX, cursorY);

		if (isCursor)
			return renderCursorCell(_board[y][x], hideShips);

		return renderNormalCell(_board[y][x], hideShips);
	}

	string buildLine(int y, int cursorX, int cursorY, const vector<Position>& previewCells, bool hideShips) const
	{
		string line;

		line += (char)186;

		for (int x = 0; x < WIDTH; x++)
			line += renderCell(x, y, cursorX, cursorY, previewCells, hideShips);

		line += (char)186;

		return line;
	}

	vector<string> getBoardLines(int cursorX = -1, int cursorY = -1, const Ship* previewShip = nullptr, 
		bool hideShips = false) const
	{
		vector<string> lines;

		lines.push_back(createTopBorder());

		vector<Position> previewCells;

		if (previewShip != nullptr)
			previewCells = previewShip->getCells();

		for (int y = 0; y < HEIGHT; y++)
			lines.push_back(buildLine(y, cursorX, cursorY, previewCells, hideShips));

		lines.push_back(createBottomBorder());

		return lines;
	}

	void draw(int cursorX = -1, int cursorY = -1, const Ship* previewShip = nullptr, bool hideShips = false) const
	{
		vector<string> lines = getBoardLines(cursorX, cursorY, previewShip, hideShips);

		for (const auto& line : lines)
			cout << line << endl;
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

		throw runtime_error("Ship not found!");
	}

	bool isAlreadyAttackedCell(int x, int y) const
	{
		return _board[y][x] == Hit || _board[y][x] == Miss || _board[y][x] == Destroyed;
	}

	void destroyShipCells(const Ship& ship)
	{
		for (const auto& cell : ship.getCells())
			_board[cell.y][cell.x] = Destroyed;
	}

	AttackResult handleShipHit(Ship& ship, int x, int y)
	{
		ship.hit();

		if (ship.isDestroyed())
		{
			destroyShipCells(ship);
			return DestroyedShip;
		}

		_board[y][x] = Hit;

		return Hitted;
	}

	AttackResult attack(int x, int y)
	{
		if (!isInside(x, y))
			throw out_of_range("Attack coordinates are outside the board!");

		if (isAlreadyAttackedCell(x, y))
			return AlreadyAttacked;

		if (_board[y][x] == ShipCell)
		{
			Ship* ship = findShipAtPosition(x, y);

			if (ship != nullptr)
				return handleShipHit(*ship, x, y);
		}

		_board[y][x] = Miss;

		return Missed;
	}

	void clearBoard()
	{
		_ships.clear();

		for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
				_board[y][x] = Empty;
	}

	int aliveShipsCount() const
	{
		int count = 0;

		for (const auto& ship : _ships)
			if (!ship.isDestroyed())
				count++;

		return count;
	}
};