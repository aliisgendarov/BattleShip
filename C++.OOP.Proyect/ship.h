#pragma once

enum Direction
{
	Horizontal,
	Vertical
};

enum ShipSize
{
	one = 1,
	two,
	three
};

struct Position
{
	int x;
	int y;
};

class Ship
{
private:
	ShipSize _size;
	int _health;
	Direction _direction;
	Position _startPosition;
	bool _destroyed;

public:
	Ship() = delete;

	Ship(ShipSize size, Direction direction, Position startPosition)
		: _size(size), _health(size), _direction(direction), _startPosition(startPosition), _destroyed(false) {}

	int getSize() const { return _size; }
	int getHealth() const { return _health; }
	Direction getDirection() const { return _direction; }
	Position getStartPosition() const { return _startPosition; }
	bool isDestroyed() const { return _destroyed; }

	void setPosition(Position position) { this->_startPosition = position; }
	void setDirection(Direction direction) { this->_direction = direction; }
	void setSize(ShipSize size)
	{
		this->_size = size;
		this->_health = size;
	}

	void rotate()
	{
		if (_direction == Direction::Horizontal) _direction = Direction::Vertical;
		else _direction = Direction::Horizontal;
	}

	void hit()
	{
		if (_health > 0)
			_health--;

		if (_health == 0)
			_destroyed = true;
	}

	vector<Position> getCells() const
	{
		vector<Position> cells;

		for (int i = 0; i < _size; i++)
		{
			Position pos = _startPosition;

			if (_direction == Direction::Horizontal)
				pos.x += i;
			else
				pos.y += i;

			cells.push_back(pos);
		}

		return cells;
	}
};