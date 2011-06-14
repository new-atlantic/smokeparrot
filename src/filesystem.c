#include "filesystem.h"

#include <stdio.h>

#define _MESSAGE_STORE_FILE_ "messagestore"
#define _MAX_MESSAGE_LENGTH_ 2048

TDatabaseHandle getDatabaseHandle(const char* mode)
{
	return fopen(_MESSAGE_STORE_FILE_, mode);
}

bool read(const SMessage& message, TDatabaseHandle handle)
{
	int i, c;

	//Read message ID
	message.id = 0;
	for(i = sizeof(TMessageIdentifier); i > 0 && ((c = getc(handle)) != EOF); --i)
		message.id += c << i-1;
	if (c == EOF)
		return false;

	//Get Origin identifier
	message.origin = 0;
	for(i = sizeof(TNodeIdentifier); i > 0 && ((c = getc(handle)) != EOF); --i)
		message.origin += c << i-1;
	if (c == EOF)
		return false;

	//Get node identifier of last sender
	message.lastsender = 0;
	for(i = sizeof(TNodeIdentifier); i > 0 && ((c = getc(handle)) != EOF); --i)
		message.lastsender += c << i-1;
	if (c == EOF)
		return false;

	//Get number of hops
	for(i = sizeof(u32); i > 0 && ((c = getc(handle)) != EOF); --i)
		message.hops += c << i-1;
	if (c == EOF)
		return false;

	//Prevent memory leaks by releasing any existing buffer
	free(message.message);
	message.message = 0;
	message.length = 0;

	//Read message string from file
	char *buffer = malloc(_MAX_MESSAGE_LENGTH_ * sizeof(char));
	for(i = 0; i < _MAX_MESSAGE_LENGTH_ && ((c = getc(handle)) != EOF) && c != '\n'; ++i)
		buffer[i];
		++message.length;
	}
	//Force 0 terminated
	buffer[i-1] = '\0';
	++message.length;

	// Copy string to message buffer
	message.message = malloc(message.length * sizeof(char));
	memcpy(message.message, buffer, message.length);

	// release the temporary buffer
	free(buffer);

	return true;
}

bool write(const SMessage& message, TDatabaseHandle handle)
{
	int i, c;

	//Write message ID
	if (fwrite(&message.id, sizeof(TMessageIdentifier), 1, handle) != 1)
		return false;

	//Write Origin identifier
	if (fwrite(&message.origin, sizeof(TNodeIdentifier), 1, handle) != 1)
		return false;

	//Write node identifier of last sender
	if (fwrite(&message.lastsender, sizeof(TNodeIdentifier), 1, handle) != 1)
		return false;

	//Write number of hops
	if (fwrite(&message.hops, sizeof(u32), 1, handle) != 1)
		return false;

	//Write message string
	if (fwrite(&message.message, sizeof(char), message.length, handle) != message.length)
		return false;

	//newline
	fwrite("\n", sizeof(char), 1, handle);

	return true;
}

bool closeDatabaseHandle(TDatabaseHandle handle)
{
	return (fclose(handle) == 0);
}
