#pragma once

class BotClass
{
private:
	vector<Position> _targets;
	vector<Position> _hits;
	vector<Position> _forbiddenPositions;

public:
	BotClass() = default;

	bool isValidAttack(Board& board, int x, int y) // verilen kordinati vurmaq olar yoxsa yox
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

	bool existsTarget(Position pos) // eyni kordinati targete elave etmesin, yeni vurulan yer birdaha vurulmasin deye yoxlama
	{
		for (const auto& p : _targets)
			if (p.x == pos.x && p.y == pos.y)
				return true;

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

	Position getTargetMove(Board& enemyBoard)
	{
		while (!_targets.empty())
		{
			Position pos = _targets.back();

			_targets.pop_back();

			if (isValidAttack(enemyBoard, pos.x, pos.y))
				return pos;
		}

		return { -1, -1 };
	}

	Position getCheckerboardMove(Board& enemyBoard) // 100 huceyreni axtarib tapmaqa calismaqdansa 50 huceyreni axtarib boyuk gemileri tapmaqa calisir
	{
		for (int i = 0; i < 100; i++)
		{
			int x = rand() % 10;
			int y = rand() % 10;

			if ((x + y) % 2 == 0 && isValidAttack(enemyBoard, x, y))
				return { x, y };
		}

		return { -1, -1 };
	}

	Position getRandomMove(Board& enemyBoard)
	{
		while (true)
		{
			int x = rand() % 10;
			int y = rand() % 10;

			if (isValidAttack(enemyBoard, x, y))
				return { x, y };
		}
	}

	Position makeMove(Board& enemyBoard)
	{
		Position move = getTargetMove(enemyBoard);

		if (move.x != -1)
			return move;

		move = getCheckerboardMove(enemyBoard);

		if (move.x != -1)
			return move;

		return getRandomMove(enemyBoard);
	}

	bool isForbidden(Position pos)
	{
		for (const auto& p : _forbiddenPositions)
			if (p.x == pos.x && p.y == pos.y)
				return true;

		return false;
	}

	void addAdjacentTargets(Board& board, Position pos)
	{
		addTarget(board, pos.x + 1, pos.y);
		addTarget(board, pos.x - 1, pos.y);
		addTarget(board, pos.x, pos.y + 1);
		addTarget(board, pos.x, pos.y - 1);
	}
	void addDirectionalTargets(Board& board) // gemi ucludurse ve artiq 2 hissesi tapilibsa elave yoxlamalara ehtiyac yoxdur
	{
		Position first = _hits[0];
		Position second = _hits[1];

		if (first.x == second.x)
		{
			int minY = first.y;
			int maxY = first.y;

			for (const auto& h : _hits)
			{
				if (h.y < minY)
					minY = h.y;

				if (h.y > maxY)
					maxY = h.y;
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
				if (h.x < minX)
					minX = h.x;

				if (h.x > maxX)
					maxX = h.x;
			}

			addTarget(board, minX - 1, first.y);
			addTarget(board, maxX + 1, first.y);
		}
	}
	void addForbiddenPositionsAround(Position pos) // geminin 1 cell yaxinliqinda gemi ola bilmez deye onu qadaganlara elave edib onu birdaha yoxlamiriq
	{
		for (int yy = pos.y - 1; yy <= pos.y + 1; yy++)
		{
			for (int xx = pos.x - 1; xx <= pos.x + 1; xx++)
			{
				Position p = { xx, yy };

				if (!existsTarget(p) && !isForbidden(p))
					_forbiddenPositions.push_back(p);
			}
		}
	}
	void handleHit(Board& board, Position pos)
	{
		_hits.push_back(pos);

		if (_hits.size() >= 2)
			addDirectionalTargets(board);
		else
			addAdjacentTargets(board, pos);
	}
	void handleDestroyedShip(Position pos)
	{
		_targets.clear();

		for (const auto& hit : _hits)
			addForbiddenPositionsAround(hit);

		addForbiddenPositionsAround(pos);

		_hits.clear();
	}
	void processResult(Board& board, Position pos, AttackResult result)
	{
		if (result == Hitted)
			handleHit(board, pos);
		else if (result == DestroyedShip)
			handleDestroyedShip(pos);
	}
};