

struct SMessage {
	TMessageIdentifier id;
	TNodeIdentifier origin;
	char* message;
	list<TMessageIdentifier> senders;
	u32 hops;
};

SMessage createMessage(char* message);
