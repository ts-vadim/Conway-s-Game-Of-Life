#pragma once

#include "IEventListener.h"


class IEventPublisher
{
public:
	virtual ~IEventPublisher() {};
	virtual void Attach(IEventListener* listener) = 0;
	virtual void Detach(IEventListener* listener) = 0;
	virtual void Notify() = 0;
};

