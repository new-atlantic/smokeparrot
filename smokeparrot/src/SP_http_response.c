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


#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MHD_PLATFORM_H
#include <microhttpd.h>

#include "SP_http_response.h"
#include "SP_message.h"


// Resources served
#define SP_URI_SMOKEPARROT "/smokeparrot"
#define SP_URI_MESSAGES    "/smokeparrot/messages"
#define SP_URI_MESSAGE     "/smokeparrot/message"
#define SP_URI_NEW_MESSAGE "/smokeparrot/message/new"


static int resource_not_found (struct MHD_Connection *connection,
                               const char *url);

static int method_not_supported (struct MHD_Connection *connection,
                                 const char *url,
                                 const char *method);

static int GET_root_resource (struct MHD_Connection *connection);

static int GET_smokeparrot_resource (struct MHD_Connection *connection);

static int GET_messages_resource (struct MHD_Connection *connection);

static int GET_message_resource (struct MHD_Connection *connection);

static int POST_new_message (struct MHD_Connection *connection,
                             const char *upload_data,
                             size_t *upload_data_size);

static int POST_message (struct MHD_Connection *connection,
                         const char *url,
                         const char *upload_data,
                         size_t *upload_data_size);

/**
 * @brief Default callback for responding to HTTP requests
 *
 * @param *cls
 * @param *connection Handle to the HTTP connection / request
 * @param *url Request path
 * @param *method HTTP request method
 * @param *version HTTP version string
 * @param upload_data Data being uploaded
 * @param upload_data_size Size of the uploaded data
 * @param con_cls
 *
 * SP_request_callback parses the request and returns the appropriate response.
 */

int SP_request_callback (void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **con_cls) 
{
  /* Create response based on request method and path */

	if (! strcmp (url, "/")) {
		return GET_root_resource (connection);
	} else if (! strcmp (url, SP_URI_SMOKEPARROT)) {
		if (! strcmp (method, "GET")) {
			return GET_smokeparrot_resource (connection);
		} else {
			return method_not_supported (connection, url, method);
		}
	} else if (! strcmp (url, SP_URI_MESSAGES)) {
		if (! strcmp (method, "GET")) {
			return GET_messages_resource (connection);
		} else {
			return method_not_supported (connection, url, method);
		}
	} else if (! strcmp (url, SP_URI_NEW_MESSAGE)) {
		if (! strcmp (method, "POST")) {
			return POST_new_message (connection,
			                         upload_data,
			                         upload_data_size);
		} else {
			return method_not_supported (connection, url, method);
		}
	} else if (! strncmp (url, SP_URI_MESSAGE, strlen (SP_URI_MESSAGE))) {
		if (strlen (url) == strlen (SP_URI_MESSAGE)
		                           + SP_MESSAGE_ID_LENGTH + 1) {
			if (! strcmp (method, "GET")) {
				return GET_message_resource (connection);
			} else if (! strcmp (method, "POST")) {
				return POST_message (connection,
				                     url,
				                     upload_data,
				                     upload_data_size);
			} else {
				return method_not_supported (connection,
				                             url,
				                             method);
			}
		} else {
			return resource_not_found (connection, url);
		}
	} else {
		return resource_not_found (connection, url);
	}
}

static int resource_not_found (struct MHD_Connection *connection,
                               const char *url)
{
	const char *data = "404: Resource not found.\n";
	// const char *data = url;
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "text/plain");
	queue_result = MHD_queue_response (connection, 
	                                   MHD_HTTP_NOT_FOUND,
	                                   response);
	MHD_destroy_response (response);
	return queue_result;
};

static int method_not_supported (struct MHD_Connection *connection,
                                 const char *url,
                                 const char *method)
{
	const char *data = "405: Method not supported.\n";
	// const char *data = url;
	// const char *data = method;
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "text/plain");
	queue_result = MHD_queue_response (connection,
	                                   MHD_HTTP_METHOD_NOT_ALLOWED,
	                                   response);
	MHD_destroy_response (response);
	return queue_result;
};

static int GET_root_resource (struct MHD_Connection *connection)
{
	const char *data = "";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_LOCATION,
	                         "/smokeparrot");
	queue_result = MHD_queue_response (connection,
	                                   MHD_HTTP_MOVED_PERMANENTLY,
	                                   response);
	MHD_destroy_response (response);
	return queue_result;
};

static int GET_smokeparrot_resource (struct MHD_Connection *connection)
{
	const char *data = "Program: Smokeparrot\n" \
	                   "Version: 0.0\n"         \
	                   "Protocol: TCP/IPv4; TCP/IPv6\n";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "text/plain");
	queue_result = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	return queue_result;
};

static int GET_messages_resource (struct MHD_Connection *connection)
{
	const char *data = "{\n"                      \
	                   "\"SP_MessageList\": []\n"	\
	                   "}\n";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "application/json");
	queue_result = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	return queue_result;
};

static int GET_message_resource (struct MHD_Connection *connection)
{
	const char *data = "{\n"                    \
	                   "\"SP_Message\": null\n" \
	                   "}\n";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "application/json");
	queue_result = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	return queue_result;
};

static int POST_new_message (struct MHD_Connection *connection,
                             const char *upload_data,
                             size_t *upload_data_size)
{
	const char *data = "POST new message\n";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "text/plain");
	queue_result = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	return queue_result;
};

static int POST_message (struct MHD_Connection *connection,
			     const char *url,
			     const char *upload_data, 
			     size_t *upload_data_size)
{
	const char *data = "POST message\n";
	struct MHD_Response *response;
	int queue_result;

	response = MHD_create_response_from_buffer (strlen (data),
	                                            (void*) data,
	                                            MHD_RESPMEM_PERSISTENT);
	MHD_add_response_header (response,
	                         MHD_HTTP_HEADER_CONTENT_TYPE,
	                         "text/plain");
	queue_result = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);
	return queue_result;
};

