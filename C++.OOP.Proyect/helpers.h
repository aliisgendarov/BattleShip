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

void selectShipMenu(Board& board, Ship& currentShip, int cursorX, int cursorY, int currentPlayer)
{
    int selectedIndex = 0;
    bool selectRunning = true;

    while (selectRunning)
    {
        system("cls || clear");

        cout << "Player " << currentPlayer << endl;

        board.draw(cursorX, cursorY, &currentShip);

        cout << "Press 'f' to select ship\n";
        cout << (selectedIndex == 0 ? "->>" : "") << "1)Count of one cell ships - " << board.getOneCellCount()
            << (selectedIndex == 0 ? " <<-" : "") << endl;
        cout << (selectedIndex == 1 ? "->>" : "") << "2)Count of two cell ships - " << board.getTwoCellCount()
            << (selectedIndex == 1 ? " <<-" : "") << endl;
        cout << (selectedIndex == 2 ? "->>" : "") << "3)Count of three cell ships - " << board.getThreeCellCount()
            << (selectedIndex == 2 ? " <<-" : "") << endl;

        int key = _getch();

        keyUpAndDownMove(key, selectedIndex, 2);

        switch (key)
        {
        case Enter:

            switch (selectedIndex)
            {
            case 0:

                if (board.getOneCellCount() == 0)
                    break;

                currentShip.setSize(one);

                selectRunning = false;

                break;
            case 1:

                if (board.getTwoCellCount() == 0)
                    break;

                currentShip.setSize(two);

                selectRunning = false;

                break;
            case 2:

                if (board.getThreeCellCount() == 0)
                    break;

                currentShip.setSize(three);

                selectRunning = false;

                break;
            }
            break;
        }
    }
}