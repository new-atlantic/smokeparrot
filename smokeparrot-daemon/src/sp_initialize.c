/**
 * @file sp_initialize.c
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

/* 
 * Parts of the code are adapted from
 * http://siber.cankaya.edu.tr/ozdogan/SystemsProgramming/ceng425/node22.html
 * and Michael Kerrisk's "The Linux Programming Interface".
 * See http://man7.org/tlpi.
 */


/* INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "sp_initialize.h"
#include "sp_common.h"


/* DEFINES */

#define PID_FILE_BUFFER_SIZE 100


/* GLOBAL VARIABLES */

extern const char *program_name;


/* FUNCTION BODIES */

void
print_usage (FILE * stream, int exit_code)
{
  fprintf (stream, _("Usage:  %s options\n"), program_name);
  fprintf (stream,
         _("  -h  --help                Display this usage information.\n"
	   "  -d  --daemon              Run in background.\n"
	   "  -k  --kill                Kill smokeparrot running in daemon mode.\n"
	   "  -c  --config-file FILE    Use configuration file FILE.\n"
	   "  -p  --pid-file FILE       Use pid-file FILE.\n"
	   "  -l  --log-file FILE       Use log-file FILE.\n"
	   "  -v  --verbose             Print verbose messages.\n"
	   "  -V  --version             Prints the program version.\n"));
  exit (exit_code);
}

int
create_pid_file (const char *pid_file)
{
  int file_descriptor;
  char pid_file_buffer[PID_FILE_BUFFER_SIZE];
  struct flock file_lock;

  file_descriptor = open (pid_file, O_RDWR | O_CREAT, 00600);

  file_lock.l_type = (short int) F_WRLCK;
  file_lock.l_whence = (short int) SEEK_SET;
  file_lock.l_start = 0;
  file_lock.l_len = 0;

  if (file_descriptor == -1)
    {
      return -1;
    }

  if (fcntl (file_descriptor, F_SETFD, FD_CLOEXEC) == -1)
    {
      return -1;
    }

  if (fcntl (file_descriptor, F_SETLK, &file_lock) == -1)
    {
      return -1;
    }

  if (ftruncate (file_descriptor, 0) == -1)
    {
      return -1;
    }

  snprintf (pid_file_buffer, PID_FILE_BUFFER_SIZE, "%ld\n", (long) getpid ());
  if (write (file_descriptor, pid_file_buffer, strlen (pid_file_buffer)) !=
      (ssize_t) strlen (pid_file_buffer))
    {
      return -1;
    }

  return file_descriptor;
}
