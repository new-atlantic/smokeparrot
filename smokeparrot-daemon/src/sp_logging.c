/**
 * @file sp_logging.c
 * @brief Logging facilities for the Smokeparrot daemon.
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

/* 
 * Parts of the code are adapted from Michael Kerrisk's "The Linux Programming
 * Interface". See http://man7.org/tlpi.
 */


/* INCLUDES */

#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include "sp_logging.h"


/* DEFINES */

#define TIMESTAMP_BUFFER_SIZE sizeof("YYYY-MM-DD HH:MM:SS")
#define TIMESTAMP_FORMAT "%F %X"


/* LOCAL VARIABLES */

/**
 * @brief The stream to which log messages are written.
 *
 * Usually directed to the log file that is specified using the -l or --log-file
 * command line option.
 **/
static FILE *log_file_stream;


/* FUNCTION BODIES */

int
open_log_file (const char *log_file)
{
  mode_t mask;
  mask = umask (0077);
  log_file_stream = fopen (log_file, "a");

  if (log_file_stream == NULL)
    {
      return -1;
    }

  umask (mask);
  setbuf (log_file_stream, NULL);

  write_log_message ("Log file opened succesfully");

  return 0;
}

int
close_log_file (void)
{
  write_log_message ("Closing log file");
  if (fclose (log_file_stream) != 0)
    {
      return -1;
    }

  return 0;
}

void
write_log_message (const char *format, ...)
{
  va_list argument_list;
  char timestamp[TIMESTAMP_BUFFER_SIZE];
  time_t t;
  struct tm *local_time;

  t = time (NULL);
  local_time = localtime (&t);

  if (log_file_stream == NULL)
    /* When there is no open stream for the log file print to stdout. */
    {
      if ((local_time == NULL)
	  || (strftime (timestamp, TIMESTAMP_BUFFER_SIZE,
			TIMESTAMP_FORMAT, local_time) == 0))
	{
	  printf ("???Unknown time???: ");
	}
      else
	{
	  printf ("%s: ", timestamp);
	}

      va_start (argument_list, format);
      vprintf (format, argument_list);
      printf ("\n");
      va_end (argument_list);
    }

  else
    /* When the stream is open print to the stream. */
    {
      if ((local_time == NULL)
	  || (strftime (timestamp, TIMESTAMP_BUFFER_SIZE,
			TIMESTAMP_FORMAT, local_time) == 0))
	{
	  fprintf (log_file_stream, "???Unknown time???: ");
	}
      else
	{
	  fprintf (log_file_stream, "%s: ", timestamp);
	}

      va_start (argument_list, format);
      vfprintf (log_file_stream, format, argument_list);
      fprintf (log_file_stream, "\n");
      va_end (argument_list);
    }
}
