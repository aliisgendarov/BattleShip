#pragma once

void keyUpAndDownMove(int ch,int& c, int count)
{
	switch (ch)
	{
	case KeyUp:
		c > 0 ? c-- : c = 0;
		break;
	case KeyDown:
		c < count ? c++ : c = count;
		break;
	}
}

void drawBoards(Board& leftBoard, Board& rightBoard, int currentTurn, int attackX = -1, int attackY = -1)
{
	vector<string> leftLines;
	vector<string> rightLines;

	if (currentTurn == 1)
	{
		leftLines = leftBoard.getBoardLines(-1, -1, nullptr, true);
		rightLines = rightBoard.getBoardLines(attackX, attackY, nullptr, true);
	}
	else
	{
		leftLines = leftBoard.getBoardLines(attackX, attackY, nullptr, true);
		rightLines = rightBoard.getBoardLines(-1, -1, nullptr, true);
	}

	cout << "PLAYER 1 BOARD" << "\t\t\t" << "PLAYER 2 BOARD\n";

	for (size_t i = 0; i < leftLines.size(); i++)
		cout << leftLines[i] << "\t\t" << rightLines[i] << endl;
}

