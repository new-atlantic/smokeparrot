/**
 * @file sp_initialize.h
 * @brief Assisting functions for main() in smokeparrot.c.
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
 * @param exit_code The exit code to use when calling \c exit().
 *
 * Prints usage information for this program to STREAM (typically stdout or 
 * stderr), and exits the program with the specified  * EXIT_CODE.  Does not
 * return.
 **/
void print_usage (FILE * stream, int exit_code);

/**
 * @brief Creates a locked file to ensure that only one instance of the daemon
 *        is running.
 *
 * @param *pid_file Pointer to the pid-file to be used.
 *
 * @retval -1 Creating or locking the pid-file failed.
 * @retval file_descriptor File descriptor for the pid file.
 *
 * Creates and or locks the file specified with \c *pid_file. This is used to
 * ensure that only one daemon instance is running. It does not, at the moment,
 * distinguish between errors caused by a previous lock by a running instance
 * and other errors causing the function call to fail, i.e. a return value of
 * -1 does not guarantee that an instance is actually running.
 **/
int create_pid_file (const char *pid_file);

#endif
