/*
 * Copyright 2012 Torsti Schulz
 *
 * This file is part of the Smokeparrot.
 *
 * Smokeparrot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Smokeparrot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

// SP_MESSAGE_ID is a hex encoded sha256 hash.
#define SP_MESSAGE_ID_LENGTH 64

#define MESSAGE_MAX_UTF8_CHARS


struct SP_Message {
	// identifier_t id;
	// address_t    origin;
	unsigned int length;
	char*        sender;
	char*        text;
	time_t       time_sent;
	// sig_t signature;
	unsigned int hops; // shortest path;
};

struct SP_Message_Entry {
	struct SP_Message message;
	time_t            time_received; // time when message first received
	unsigned int      n_times_received;
	// address_t[]*      sender_list;
};

