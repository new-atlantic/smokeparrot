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

#ifndef SP_HTTP_RESPONSE_H
#define SP_HTTP_RESPONSE_H


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

extern int SP_request_callback (void *cls, struct MHD_Connection *connection,
                                const char *url,
                                const char *method, const char *version,
                                const char *upload_data,
                                size_t *upload_data_size, void **con_cls);

#endif

