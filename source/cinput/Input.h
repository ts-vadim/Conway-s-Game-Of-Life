#pragma once

#include <Windows.h>
#include <cstdio>
#include <string>
#include <conio.h>


class Input
{
public:
	Input();
	~Input();

	void GetString(std::string& str);
	bool AnyKey();
};

