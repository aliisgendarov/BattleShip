#define KeyUp 72
#define KeyDown 80
#define KeyRight 77
#define KeyLeft 75
#define Enter 13
#define ESC 27
#define H 104
#define V 118
#define F 102
#define Cell 178
#define Border 177

#include <iostream>
#include <cassert>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace std;


typedef unsigned short int ushort;

#include "player.h"
#include "ship.h"
#include "board.h"
#include "bot.h"
#include "helpers.h"


int main()
{
	srand(time(NULL));

	cout << "Welcome BattleShip Game";
	this_thread::sleep_for(chrono::seconds(2));

	int choise = 0;

	while (true)
	{
		system("cls || clear");

		cout << "BattleShip" << endl;
		cout << (choise == 0 ? "->>" : "") << "\033[32mStart Game" << "\033[0m" << (choise == 0 ? "<<-" : "") << endl;
		cout << (choise == 1 ? "->>" : "") << "\033[34mAbout Game" << "\033[0m" << (choise == 1 ? "<<-" : "") << endl;
		cout << (choise == 2 ? "->>" : "") << "\033[31mExit" << "\033[0m" << (choise == 2 ? "<<-" : "") << endl;

		int c = _getch();
		keyUpAndDownMove(c, choise, 2);
		switch (c)
		{
		case Enter:
			switch (choise)
			{
			case 0:
			{
				Player p1;
				Player p2;

				int cho = 0;
				bool isRunning = true;
				
				while (isRunning)
				{
					system("cls || clear");
					cout << "Select players:" << endl;

					cout << (cho == 0 ? "->>" : "") << "Player 1: "; p1.showPlayer();
					cout << "\033[0m" << (cho == 0 ? " <<-" : "") << endl;
					cout << (cho == 1 ? "->>" : "") << "Player 2: "; p2.showPlayer();
					cout << "\033[0m" << (cho == 1 ? " <<-" : "") << endl;
					cout << (cho == 2 ? "->>" : "") << "Done" << (cho == 2 ? " <<-" : "") << endl;
					cout << (cho == 3 ? "->>" : "") << "Back Menu" << (cho == 3 ? "<<-" : "") << endl;

					int cc = _getch();
					keyUpAndDownMove(cc, cho, 3);
					switch (cc)
					{
					case KeyRight:
						if (cho == 0) p1.changeForRight();
						else if (cho == 1) p2.changeForRight();
						break;
					case KeyLeft:
						if (cho == 0) p1.changeForLeft();
						else if (cho == 1) p2.changeForLeft();
						break;
					case ESC:
						isRunning = false;
						break;
					case Enter:
						switch (cho)
						{
						case 0:
							break;
						case 1:
							break;
						case 2:
						{
							Board p1Board;
							Board p2Board;

							Board* board = &p1Board;

							int currentPlayer = 1;

							int cursorX = 0;
							int cursorY = 0;

							Ship currentShip(one, Horizontal, { 0,0 });

							bool gameRunning = true;

							if (currentPlayer == 1)
							{
								if (p1.getPlayer() != "Manual")
								{
									board->placeShipsAutomatically();
									system("cls || clear");
									cout << "Player " << currentPlayer << " board automatically filled!" << endl;
									cout << "Press any key to countinue...";
									_getch();
								}
							}
							else
							{
								if (p2.getPlayer() != "Manual")
								{
									board->placeShipsAutomatically();
									system("cls || clear");
									cout << "Player " << currentPlayer << " board automatically filled!" << endl;
									cout << "Press any key to countinue...";
									_getch();
								}
							}

							while (gameRunning)
							{
								if (!board->haveShipToPut())
								{
									if (currentPlayer == 1)
									{
										currentPlayer = 2;
										board = &p2Board;
										currentShip.setSize(one);

										system("cls || clear");
										cout << "Player 2 Turn!" << endl;

										if (p2.getPlayer() != "Manual")
										{
											board->placeShipsAutomatically();
											cout << "Player " << currentPlayer << " board automatically filled!" << endl;
											cout << "Press any key to countinue...";
											_getch();
										}

									}
									else
									{
										gameRunning = false;
									}

									continue;
								}

								if (board->isShipCountFinished(currentShip) &&
									board->haveShipToPut())
								{
									int cohi = 0;
									bool selectRunning = true;

									while (selectRunning)
									{
										system("cls || clear");

										cout << "Player " << currentPlayer << endl;

										board->draw(cursorX, cursorY, &currentShip);

										cout << "Press \'f\' to select ship";
										cout << "\033[0m" << endl;
										cout << (cohi == 0 ? "->>" : "") << "1)Count of one cell ships - "
											<< board->getOneCellCount() << (cohi == 0 ? " <<-" : "") << endl;
										cout << (cohi == 1 ? "->>" : "") << "2)Count of two cell ships - "
											<< board->getTwoCellCount() << (cohi == 1 ? " <<-" : "") << endl;
										cout << (cohi == 2 ? "->>" : "") << "3)Count of three cell ships - "
											<< board->getThreeCellCount() << (cohi == 2 ? " <<-" : "") << endl;

										int k = _getch();

										keyUpAndDownMove(k, cohi, 2);

										switch (k)
										{
										case Enter:

											switch (cohi)
											{
											case 0:

												if (board->getOneCellCount() == 0)
													break;

												currentShip.setSize(one);
												selectRunning = false;
												break;
											case 1:

												if (board->getTwoCellCount() == 0)
													break;

												currentShip.setSize(two);
												selectRunning = false;
												break;
											case 2:

												if (board->getThreeCellCount() == 0)
													break;

												currentShip.setSize(three);
												selectRunning = false;
												break;
											}
										}
									}
								}

								system("cls || clear");

								currentShip.setPosition({ cursorX, cursorY });

								cout << "Player " << currentPlayer << endl;
								board->draw(cursorX, cursorY, &currentShip);
								cout << "Press \'f\' to select ship" << endl;
								cout << "1)Count of one cell ships - " << board->getOneCellCount() << endl;
								cout << "2)Count of two cell ships - " << board->getTwoCellCount() << endl;
								cout << "3)Count of three cell ships - " << board->getThreeCellCount() << endl;

								int key = _getch();
								switch (key)
								{
								case KeyUp:
									cursorY > 0 ? cursorY-- : cursorY = 0;
									break;
								case KeyDown:
									if (cursorY < 9 && board->moveChek(currentShip, 0, 1))
										cursorY++;
									break;
								case KeyLeft:
									if (cursorX > 0)
										cursorX--;
									break;
								case KeyRight:
									if (cursorX < 9 && board->moveChek(currentShip, 1, 0))
										cursorX++;
									break;
								case H:
									if (currentShip.getDirection() == Vertical)
										board->rotateCheckAndDone(currentShip);
									break;

								case V:
									if (currentShip.getDirection() == Horizontal)
										board->rotateCheckAndDone(currentShip);
									break;

								case F:
								{
									int cohi = 0;
									bool selectRunning = true;

									while (selectRunning)
									{
										system("cls || clear");
										cout << "Player " << currentPlayer << endl;
										board->draw(cursorX, cursorY, &currentShip);
										cout << "Press \'f\' to select ship";
										cout << "\033[0m" << (cho == 0 ? " <<-" : "") << endl;
										cout << (cohi == 0 ? "->>" : "") << "1)Count of one cell ships - " << board->getOneCellCount()
											<< (cohi == 0 ? " <<-" : "") << endl;
										cout << (cohi == 1 ? "->>" : "") << "2)Count of two cell ships - " << board->getTwoCellCount()
											<< (cohi == 1 ? " <<-" : "") << endl;
										cout << (cohi == 2 ? "->>" : "") << "3)Count of three cell ships - " << board->getThreeCellCount()
											<< (cohi == 2 ? " <<-" : "") << endl;
										int k = _getch();
										keyUpAndDownMove(k, cohi, 2);
										switch (k)
										{
										case Enter:
											switch (cohi)
											{
											case 0:
												if (board->getOneCellCount() == 0)
													break;
												currentShip.setSize(one);
												selectRunning = false;
												break;
											case 1:
												if (board->getTwoCellCount() == 0)
													break;
												currentShip.setSize(two);
												selectRunning = false;
												break;
											case 2:
												if (board->getThreeCellCount() == 0)
													break;
												currentShip.setSize(three);
												selectRunning = false;
												break;
											}
										}
									}

									break;
								}
								case Enter:
								{
									board->placeShip(currentShip);
									break;
								}

								case ESC:
								{
									gameRunning = false;
									break;
								}
								}
							}

							int attackX = 0;
							int attackY = 0;

							int currentTurn = 1;

							BotClass bot1;
							BotClass bot2;

							bool battleRunning = true;

							while (battleRunning)
							{
								bool isBotTurn = false;

								if (currentTurn == 1)
									isBotTurn = p1.getPlayer() == "Bot";
								else
									isBotTurn = p2.getPlayer() == "Bot";

								system("cls || clear");

								cout << "PLAYER " << currentTurn << " TURN\n\n";

								drawBoards(p1Board, p2Board, currentTurn, attackX, attackY);

								int key = 0;

								if (!isBotTurn)
								{
									key = _getch();
								}
								else
								{
									Position move;

									if (currentTurn == 1)
										move = bot1.makeMove(p2Board);
									else
										move = bot2.makeMove(p1Board);

									attackX = move.x;
									attackY = move.y;

									key = Enter;

									this_thread::sleep_for(chrono::milliseconds(500));
								}

								switch (key)
								{
								case KeyUp:

									if (attackY > 0)
										attackY--;

									break;

								case KeyDown:

									if (attackY < 9)
										attackY++;

									break;

								case KeyLeft:

									if (attackX > 0)
										attackX--;

									break;

								case KeyRight:

									if (attackX < 9)
										attackX++;

									break;

								case Enter:
								{
									AttackResult result;

									if (currentTurn == 1)
										result = p2Board.attack(attackX, attackY);
									else
										result = p1Board.attack(attackX, attackY);

									system("cls || clear");

									drawBoards(p1Board, p2Board, currentTurn, attackX, attackY);


									bool gameOver = false;

									if (currentTurn == 1)
									{
										if (p2Board.aliveShipsCount() == 0)
											gameOver = true;
									}
									else
									{
										if (p1Board.aliveShipsCount() == 0)
											gameOver = true;
									}

									if (gameOver)
									{
										system("cls || clear");

										drawBoards(p1Board, p2Board, currentTurn);

										cout << "\nPLAYER " << currentTurn << " WINS!\n";

										battleRunning = false;

										_getch();

										break;
									}

									if (isBotTurn)
									{
										Position pos = { attackX, attackY };

										if (currentTurn == 1)
											bot1.processResult(p2Board, pos, result);
										else
											bot2.processResult(p1Board, pos, result);
									}

									if (result != AlreadyAttacked)
										currentTurn = currentTurn == 1 ? 2 : 1;

									attackX = 0;
									attackY = 0;

									break;
								}
								}
							}
							break;
						}
						case 3:
							isRunning = false;
							break;
						}
					}
				}


				break;
			}
			case 1:
				system("cls || clear");
				cout << "========== ABOUT GAME ==========" << endl << endl;

				cout << "BattleShip is a strategic naval battle game played between two players." << endl;
				cout << "The objective is to destroy all enemy ships before your opponent destroys yours.\n\n";

				cout << "Features:\n- Manual and automatic ship placement\n- Player vs Player and Bot modes\n";
				cout << "- Smart bot AI system\n- Colored hit and miss effects\n- Real-time ship status information\n\n";

				cout << "Ship Rules:\n- Ships cannot touch each other\n- Ships can be placed horizontally or vertically\n";
				cout << "- Rotation is blocked outside the map\n\n";

				cout << "Battle Symbols:\nM = Miss\nH = Hit\nA = Destroyed ship\n\n";

				cout << "Controls:\nArrow Keys -> Move\nEnter -> Select\nF -> Choose ship\nH/V -> Rotate ship\nESC -> Back/Menu\n";
				break;
			case 2:
				system("cls || clear");
				cout << "Game over!" << endl;
				return 0;
			default:
				cout << "This code is not valid!" << endl;
				break;
			}
			cout << "\nPress any key to countinue...";
			_getch();
		}
	}
	return EXIT_SUCCESS;
}