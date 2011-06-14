#include "filesystem.h"
#include "SMessageStore.h"

#define _MESSAGE_LIFETIME_ 259200

//Writes messages in queue to database
bool write_messages(SMessageQueue list)
{
	//Get database handle
	TDatabaseHandle handle = getDataBaseHandle("wb");
	if (!handle) return false;

	//Write all items in list
	while (list.used > 0) {
		SMessage message = SMessageQueue_pop(list);
		write(message, handle);
	}
	//Release handle
	closeDatabaseHandle(handle);
}

//! Retrieves messages from database
bool Store_cleanup()
{
	//Get database handle
	TDatabaseHandle handle = getDataBaseHandle("rb");
	if (!handle) return false;
	
	SMessageQueue queue;

	//read until we don't get a full item.  Add all kept items to queue.
	SMessage message;
	while (read(message, handle)) {
		if (message.archived || message.received > (time() - _MESSAGE_LIFETIME_))
		SMessageQueue_push(list, message);
	}
	//Release handle
	closeDatabaseHandle(handle);
	
	//write queue back to database
	write_messages(queue);
}

//! Adds a message to the message store
bool Store_push_message(const SMessage& message)
{
	//Get database handle
	TDatabaseHandle handle = getDataBaseHandle("ab");
	if (!handle) return false;

	bool saved = write(message, handle);

	//Release handle
	closeDatabaseHandle(handle);

	return saved;
}

//! Retrieves messages from database
struct SMessageQueue Store_read_messages()
{
	//Get database handle
	TDatabaseHandle handle = getDataBaseHandle("rb");
	if (!handle) return struct SMessageQueue;
	
	SMessageQueue queue;

	//read until we don't get a full item.  Add all items to queue
	SMessage message;
	while (read(message, handle)) {
		SMessageQueue_push(list, message);
	}
	//Release handle
	closeDatabaseHandle(handle);
	return queue;
}
