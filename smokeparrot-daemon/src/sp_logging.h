/**
 * @file sp_logging.h
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

#ifndef SP_LOGGING_H
#define SP_LOGGING_H

/**
 * @brief Opens log file for writing.
 *
 * @param log_file Name (path) of the logfile.
 *
 * @retval  0 Log file opened succesfully as stream.
 * @retval -1 Opening the log file failed.
 *
 * Opens a stream for writing to the LOG_FILE. The process must have create or
 * write privileges for that file.
 **/
int open_log_file (const char *log_file);

/**
 * @brief Closes the log file.
 *
 * @retval  0 Log file closed succesfully.
 * @retval -1 Closing the log file failed.
 *
 * Closes the stream that was opened for writing to the log file with
 * \c open_log_file().
 *
 **/
int close_log_file (void);

/**
 * @brief Writes a message to the log file.
 *
 * @param *format Format string for variable number of arguments.
 * @param ... Additional arguments to \c format.
 *
 * Writes a timestamped message to the log file opened with \c open_log_file().
 * If the file has not been opened, prints to standard out. Does not return.
 **/
void write_log_message (const char *format, ...);

#endif
