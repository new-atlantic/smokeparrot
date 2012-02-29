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
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define MHD_PLATFORM_H
#include <microhttpd.h>

#include "SP_http_response.h"


#define SP_SERVER_PORT 1687


int main ()
{
	struct MHD_Daemon *http_daemon;

	/* TODO: Third argument needs callback to check if client is allowed to
	   connect. Check via MeshAware if is in range. Check via auth if allowed
	   to connect automatically. Fourth argument passes extra arguments to 3rd */

	/* TODO: Set options for number of connections, number of connections per IP,
	   and memory per connection */

	http_daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY |
	                                MHD_USE_DEBUG |
	                                MHD_USE_PEDANTIC_CHECKS,
	                                SP_SERVER_PORT,
	                                NULL,
	                                NULL,
	                                &SP_request_callback,
	                                NULL,
	                                MHD_OPTION_END);

	if (http_daemon)  {
		;
	} else {
		exit (EXIT_FAILURE);
	}

	// TODO: become daemon
	sleep (300);
	MHD_stop_daemon (http_daemon);
	exit (EXIT_SUCCESS);
}

