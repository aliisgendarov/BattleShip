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

