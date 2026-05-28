#pragma once

class BotClass
{
private:
	vector<Position> _targets;
	vector<Position> _hits;
	vector<Position> _forbiddenPositions;

public:

	BotClass() = default;

	bool isValidAttack(Board& board, int x, int y)
	{
		if (!board.isInside(x, y))
			return false;

		CellState state = board.getCellState(x, y);

		if (state == Hit || state == Miss || state == Destroyed)
			return false;

		if (isForbidden({ x,y }))
			return false;

		return true;
	}

	bool existsTarget(Position pos)
	{
		for (const auto& p : _targets)
		{
			if (p.x == pos.x && p.y == pos.y)
				return true;
		}

		return false;
	}

	void addTarget(Board& board, int x, int y)
	{
		if (!isValidAttack(board, x, y))
			return;

		Position pos = { x,y };

		if (!existsTarget(pos))
			_targets.push_back(pos);
	}

	Position makeMove(Board& enemyBoard)
	{
		while (!_targets.empty())
		{
			Position pos = _targets.back();

			_targets.pop_back();

			if (isValidAttack(enemyBoard, pos.x, pos.y))
				return pos;
		}

		for (int i = 0; i < 100; i++)
		{
			int x = rand() % 10;
			int y = rand() % 10;

			if ((x + y) % 2 == 0 &&
				isValidAttack(enemyBoard, x, y))
			{
				return Position{ x,y };
			}
		}

		while (true)
		{
			int x = rand() % 10;
			int y = rand() % 10;

			if (isValidAttack(enemyBoard, x, y))
				return Position{ x,y };
		}
	}

	bool isForbidden(Position pos)
	{
		for (const auto& p : _forbiddenPositions)
		{
			if (p.x == pos.x && p.y == pos.y)
				return true;
		}

		return false;
	}

	void processResult(Board& board, Position pos, AttackResult result)
	{
		if (result == Hitted)
		{
			_hits.push_back(pos);

			if (_hits.size() >= 2)
			{
				Position first = _hits[0];
				Position second = _hits[1];

				if (first.x == second.x)
				{
					int minY = first.y;
					int maxY = first.y;

					for (const auto& h : _hits)
					{
						if (h.y < minY) minY = h.y;
						if (h.y > maxY) maxY = h.y;
					}

					addTarget(board, first.x, minY - 1);
					addTarget(board, first.x, maxY + 1);
				}
				else if (first.y == second.y)
				{
					int minX = first.x;
					int maxX = first.x;

					for (const auto& h : _hits)
					{
						if (h.x < minX) minX = h.x;
						if (h.x > maxX) maxX = h.x;
					}

					addTarget(board, minX - 1, first.y);
					addTarget(board, maxX + 1, first.y);
				}
			}
			else
			{
				addTarget(board, pos.x + 1, pos.y);
				addTarget(board, pos.x - 1, pos.y);
				addTarget(board, pos.x, pos.y + 1);
				addTarget(board, pos.x, pos.y - 1);
			}
		}

		else if (result == DestroyedShip)
		{
			_targets.clear();

			for (const auto& hit : _hits)
			{
				for (int yy = hit.y - 1; yy <= hit.y + 1; yy++)
				{
					for (int xx = hit.x - 1; xx <= hit.x + 1; xx++)
					{
						Position pos = { xx, yy };

						if (!existsTarget(pos) && !isForbidden(pos))
							_forbiddenPositions.push_back(pos);
					}
				}
			}

			for (int yy = pos.y - 1; yy <= pos.y + 1; yy++)
			{
				for (int xx = pos.x - 1; xx <= pos.x + 1; xx++)
				{
					Position p = { xx, yy };

					if (!existsTarget(p) && !isForbidden(p))
						_forbiddenPositions.push_back(p);
				}
			}

			_hits.clear();
		}
	}
};