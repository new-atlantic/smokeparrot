/**
 * @file sp_initialize.h
 * @brief Loggin facilities for the Smokeparrot daemon.
 * @version 0.1
 **/

/*
 * Copyright 2011 Torsti Schulz
 *
 * This file is part of the Smokeparrot daemon.
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

#ifndef SP_INITIALIZE_H
#define SP_INITIALIZE_H

/**
 * @brief Prints usage information for the program and exits.
 *
 * @param stream The stream to which the message is printed.
 * @param exit_code The exit status.
 *
 * Prints usage information for this program to STREAM (typically
 * stdout or stderr), and exits the program with EXIT_CODE.  Does not
 * return.
 **/
void print_usage (FILE * stream, int exit_code);

#endif
