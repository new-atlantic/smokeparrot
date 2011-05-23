#include "interface.h"

extern "C" SP_API struct SMessageQueue SPCALLCONV retrieveMessages()
{
	struct SMessageQueue queue;
	SMessageQueue_push(queue, struct SMessage);
	SMessageQueue_push(queue, struct SMessage);
	SMessageQueue_push(queue, struct SMessage);
}

extern "C" SP_API void SPCALLCONV newMessage(char* message)
{
	//Create new message
	//Add SMessage to message store (adds to distribution set)
}

extern "C" SP_API void SPCALLCONV redistribute(<messageID>)
{
	//get message from store
	//add message to distribution set
}

extern "C" SP_API void SPCALLCONV perserve(<messageID>)
{
	//flag for non-deletion
}

extern "C" SP_API void SPCALLCONV delete(<messageID>)
{
	//remove message from store
	//prevent readding

extern "C" SP_API void SPCALLCONV blocksource(<source>)
{
	//add source to blacklist
	//delete all messages from source (as origin or immediate)
}
