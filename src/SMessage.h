#include "SNode.h"

#include <time.h>

typedef unsigned long TMessageIdentifier;

struct SMessage {
	TMessageIdentifier id;
	TNodeIdentifier origin;
	char* message;
	unsigned int length;
	TNodeList senders;
	u32 hops;
	time_t received; //received datetime
};

//! Calculates and sets the message's id
TMessageIdentifier getMessageID(SMessage& message);
