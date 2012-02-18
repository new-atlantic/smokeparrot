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


int SP_request_callback (void *cls, struct MHD_Connection *connection, 
			 const char *url, 
			 const char *method, const char *version, 
			 const char *upload_data, 
			 size_t *upload_data_size, void **con_cls);
