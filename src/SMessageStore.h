//# Interface to the message store


#include "SMessage.h"
#include "SNode.h"
#include "SMessageQueue.h"

//! Cleans up the message store (deletes old messages, etc.)
void Store_cleanup();

//! Adds a message to the message store
void Store_push_message(const SMessage& message);

//! Flags a message so it isn't removed by cleanup
void Store_save_message(TMessageIdentifier id);

//! Removes a message from the store
void Store_remove_message(TMessageIdentifier id);

//! Prevents messages with the given id from being added
void Store_ignore_message(TMessageIdentifier id);

//! Handles distribution of messages
void Store_distribute_message(TMessageIdentifier id);

//! Adds source to blacklist and deletes all messages from source (as origin or immediate)
void Store_blacklist(TNodeIdentifier id);

//! Retrieves messages from store
struct SMessageQueue Store_read_messages();
