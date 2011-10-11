/**
 * @file sp_initialize.c
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
 * Parts of the code are adapted from
 * http://siber.cankaya.edu.tr/ozdogan/SystemsProgramming/ceng425/node22.html
 */


/* INCLUDES */

#include <stdio.h>
#include <stdlib.h>

#include "sp_initialize.h"
#include "sp_common.h"

/* GLOBAL VARIABLES */

extern const char *program_name;


/* FUNCTION BODIES */

void
print_usage (FILE * stream, int exit_code)
{
  fprintf (stream, _("Usage:  %s options\n"), program_name);
  fprintf (stream,
         _("  -h  --help             Display this usage information.\n"
	   "  -d  --daemon           Run in background.\n"
	   "  -p  --pid-file file    Use pid-file file.\n"
	   "  -l  --log-file file    Use log-file file.\n"
	   "  -v  --verbose          Print verbose messages.\n"));
  exit (exit_code);
}
















/* #define PID_FILE_BUFFER_SIZE 100 */
/* static void SigHupHandler (int received_signal); */
/* static int CreatePIDFile (const char *pid_file); */
/* static volatile sig_atomic_t hup_signal_received = 0; */

/* /\* Prepares the process to run as a daemon. *\/ */
/* int */
/* Daemonize (void) */
/* { */

/*   long int max_file_descriptors; */
/*   int file_descriptor; */
/*   struct sigaction signal_action; */

/*   /\* Register new handles for SIGHUP. *\/ */
/*   sigemptyset (&signal_action.sa_mask); */
/*   signal_action.sa_flags = SA_RESTART; */
/*   signal_action.sa_handler = SigHupHandler; */

/*   if (sigaction (SIGHUP, &signal_action, NULL) == -1) */
/*     { */
/*       return -1; */
/*     } */

/*   if (setsid () == -1) */
/*     { */
/*       return -1; */
/*     } */


/*   umask (027); */
/*   chdir ("/"); */

/*   max_file_descriptors = sysconf (_SC_OPEN_MAX); */

/*   /\* If maximum number of file descriptors could not be determined */
/*      make an educated guess. *\/ */
/*   if (max_file_descriptors == -1) */
/*     { */
/*       max_file_descriptors = 8192; */
/*     } */

/*   /\* Close all open file descriptors. *\/ */
/*   for (file_descriptor = 0; (long int) file_descriptor < max_file_descriptors; */
/*        file_descriptor++) */
/*     close (file_descriptor); */

/*   close (STDIN_FILENO); */

/*   /\* Set stdin, stdout and stderr to point to /dev/null *\/ */
/*   file_descriptor = open ("/dev/null", O_RDWR); */

/*   if (file_descriptor != STDIN_FILENO) */
/*     { */
/*       return -1; */
/*     } */

/*   if (dup2 (STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) */
/*     { */
/*       return -1; */
/*     } */

/*   if (dup2 (STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO) */
/*     { */
/*       return -1; */
/*     } */

/*   /\* Create a lock file. *\/ */
/*   if (CreatePIDFile ("/tmp/smokeparrot.pid") == -1) */
/*     { */
/*       return -1; */
/*     } */

/*    */
/*     { */
/*       return -1; */
/*     } */

/*   return 0; */

/* } */

/* /\* Creates a locked file to ensure that only one instance of the daemon is  */
/*    running *\/ */
/* static int */
/* CreatePIDFile (const char *pid_file) */
/* { */
/*   int file_descriptor; */
/*   char pid_file_buffer[PID_FILE_BUFFER_SIZE]; */
/*   struct flock file_lock; */

/*   file_descriptor = open (pid_file, O_RDWR | O_CREAT, 00600); */

/*   file_lock.l_type = (short int) F_WRLCK; */
/*   file_lock.l_whence = (short int) SEEK_SET; */
/*   file_lock.l_start = 0; */
/*   file_lock.l_len = 0; */

/*   if (file_descriptor == -1) */
/*     { */
/*       return -1; */
/*     } */

/*   if (fcntl (file_descriptor, F_SETFD, FD_CLOEXEC) == -1) */
/*     { */
/*       return -1; */
/*     } */

/*   if (fcntl (file_descriptor, F_SETLK, &file_lock) == -1) */
/*     { */
/*       return -1; */
/*     } */

/*   if (ftruncate (file_descriptor, 0) == -1) */
/*     { */
/*       return -1; */
/*     } */

/*   snprintf (pid_file_buffer, PID_FILE_BUFFER_SIZE, "%ld\n", (long) getpid ()); */
/*   if (write (file_descriptor, pid_file_buffer, strlen (pid_file_buffer)) != */
/*       (ssize_t) strlen (pid_file_buffer)) */
/*     { */
/*       return -1; */
/*     } */

/*   return file_descriptor; */
/* } */

/* /\* Set hup_signal_received after receiving SIGHUP. *\/ */
/* static void */
/* SigHupHandler (int received_signal) */
/* { */
/*   write_log_message ("Received SIGHUP"); */
/*   hup_signal_received = 1; */
/* } */
