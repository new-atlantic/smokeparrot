#include "SMessageQueue.h"

void SMessageQueue_reallocate(SMessageQueue& queue, unsigned int size)
{
	if (!queue.data)
		queue.used = 0;

	struct SMessage* temp = queue.data; // Grab original buffer
	queue.data = malloc(sizeof(SMessageQueue)*size); //create new buffer

	if (!queue.data) { //If failed, rollback
		queue.data = temp;
		return;
	}
	queue.size = size; // update buffer size

	if (size < queue.used) //if new size is smaller then used count, shrink used count
		queue.used = size;

	//Copy buffer
	unsigned int i = 0;
	for(; i < queue.used; ++i) {
		queue.data[i] = temp[i];
	}

	free(temp); //release original buffer
}

void  SMessageQueue_push(SMessageQueue& queue, const SMessage& data)
{
	if (!queue.data)
		queue.size = queue.used = 0;

	if (queue.used == size) { //If the buffer is too small then reallocate it (make bigger).
		SMessageQueue_reallocate(queue, queue.size+8);
	}
	return queue.data[used++];
}

struct SMessage SMessageQueue_pop(SMessageQueue& queue)
{
	if (!queue.data)
		queue.size = queue.used = 0;

	if (queue.used == 0) return struct SMessage;
		return queue.data[--used];
}

struct SMessage SMessageQueue_get(SMessageQueue& queue, unsigned int index)
{
	if (!queue.data)
		queue.size = queue.used = 0;

	if (queue.used <= index || queue.size <= index) return struct SMessage;
		return queue.data[index];
}
