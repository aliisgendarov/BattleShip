#pragma once

enum Players
{
	Bot,
	Manual,
	Automatic
};

class Player
{
private:
	string _player;

public:
	Player() : _player("Bot") {}

	Player(Players player)
	{
		switch (player)
		{
		case 1:
			_player = "Bot";
			break;
		case 2:
			_player = "Manual";
			break;
		case 3:
			_player = "Automatic";
			break;
		}
	}

	void changeForRight(){ _player = _player == "Bot" ? "Manual" : _player == "Manual" ? "Automatic" : "Bot"; }
	void changeForLeft() { _player = _player == "Bot" ? "Automatic" : _player == "Automatic" ? "Manual" : "Bot"; }

	string getPlayer() const { return _player; }

	void showPlayer() const
	{
		_player == "Bot" ? cout << "\033[31mBot" : _player == "Manual" ? cout << "\033[34mManual" : cout << "\033[32mAutomatic";
	}

};
