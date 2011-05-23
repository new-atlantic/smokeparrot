#include "SMessage.h"

struct SMessageQueue {
	unsigned int size, used;
	struct SMessage* data;
};

void SMessageQueue_reallocate(struct SMessageQueue& queue, unsigned int size);

void  SMessageQueue_push(struct SMessageQueue& queue, const struct SMessage& data);
struct SMessage SMessageQueue_pop(struct SMessageQueue& queue);
struct SMessage SMessageQueue_get(struct SMessageQueue& queue, unsigned int index);
