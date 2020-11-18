#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::GetString(std::string& str)
{
	str = "";
	char c;
	while (true)
	{
		c = getchar();
		if (c == '\n')
			return;
		str += c;
	}
}

bool Input::AnyKey()
{
	return _kbhit();
}