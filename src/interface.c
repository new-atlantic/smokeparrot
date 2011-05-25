#include "interface.h"
#include "SMessageStore.h"

extern "C" SP_API struct SMessageQueue SPCALLCONV retrieveMessages()
{
	return Store_read_messages();
}

extern "C" SP_API void SPCALLCONV createMessage(char* str, const unsigned int length)
{
	//Create new message
	struct SMessage message;
	message.origin = SNode_this();
	message.message = malloc(sizeof(char)*length);
	int i = 0;
	for (; i < length-1; ++i) {
		message.message[i] = str[i];
	}
	message[length-1] = '\0';
	getMessageID(message);
	message.hops = 0;

	//Add SMessage to message store (and add to distribution set)
	Store_push_message(message);
	Store_distribute_message(message.id);
}

extern "C" SP_API void SPCALLCONV redistribute(TMessageIdentifier id)
{
	//add message to distribution set
	Store_distribute_message(id);
}

extern "C" SP_API void SPCALLCONV perserve(TMessageIdentifier id)
{
	//flag for non-deletion
	Store_save_message(id);
}

extern "C" SP_API void SPCALLCONV delete(TMessageIdentifier id)
{
	//remove message from store
	Store_remove_message(id);
	//prevent readding
	Store_ignore_message(id);
}

extern "C" SP_API void SPCALLCONV blocksource(TNodeIdentifier id)
{
	if (id == SNode_this()) return; //Can't block self

	//add source to blacklist
	Store_blacklist(id);
}
