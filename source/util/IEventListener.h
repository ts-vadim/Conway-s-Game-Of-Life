#pragma once

#include "EventMessage.h"


class IEventListener
{
public:
	virtual ~IEventListener() {};
	virtual void Update(EventMessage& event) = 0;
};