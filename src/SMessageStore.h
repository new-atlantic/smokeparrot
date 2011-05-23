#include "SMessage.h"
#include "SMessageQueue.h"

void push_message(const SMessage& message);
void remove_message(<messageID>);
void ignore_message(<messageID>);
void distribute_message(<messageID>);
