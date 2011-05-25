#include "SMessage.h"

struct SMessageQueue {
	unsigned int size, used;
	struct SMessage* data;
};

//! resizes the queue
void SMessageQueue_reallocate(struct SMessageQueue& queue, unsigned int size);

//! pushes a new message to the end of the queue
void  SMessageQueue_push(struct SMessageQueue& queue, const struct SMessage& data);

//! pops the message from the end of the queue
//! returns an empty message on empty queue
struct SMessage SMessageQueue_pop(struct SMessageQueue& queue);

//! gets the message from the end of the queue, leaving it
//! returns an empty message on empty queue
struct SMessage SMessageQueue_get(struct SMessageQueue& queue, unsigned int index);
