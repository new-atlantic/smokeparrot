/**
 * @file smokeparrot.c
 * @brief The Smokeparrot daemon main program.
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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <locale.h>

#include "sp_common.h"
#include "sp_initialize.h"
#include "sp_logging.h"


/* GLOBAL VARIABLES */

/**
 * @brief The name of the program.
 **/
const char *program_name;

/**
 * @brief Flag to indicate verbose mode.
 *
 * If verbose_mode is true print or log more error messages.
 **/
bool verbose_mode;

/**
 * @brief Flag to indicate daemon mode.
 *
 * If daemon_mode is true the program is run in the background as daemon.
 **/
bool daemon_mode;


/* MAIN */

/**
 * @brief The main program entry point.
 * @param argc Number of command line arguments.
 * @param *argv[] Array of pointers to the command line arguments.
 *
 * @retval EXIT_FAILURE Program terminated prematurely due to an error.
 * @retval EXIT_SUCCESS Program executed succesfully.
 *
 * The function parses and handles command line arguments and the launches the 
 * main program. If daemon_mode is set, calls \c daemon() to fork, chdir to root
 * and close stdin, stdout and stderr.
 *
 * When main() exits it returns \c EXIT_FAILURE if a wrong command line option
 * is supplied or \c daemon() fails. Otherwise it exits with \c EXIT_SUCCESS.
 **/

int
main (int argc, char *argv[])
{

  /* main.c - HANDLING OF THE PROGRAM CALL */

  int next_option;		/* Iterator for options. */

  const char *const short_options = "hvVdkc:p:l:";	/* A string listing valid short 
							   options. */

  setlocale (LC_ALL, "");

#if ENABLE_NLS
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif

  /* An array describing valid long options.  */
  const struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'},
    {"version", no_argument, NULL, 'V'},
    {"daemon", no_argument, NULL, 'd'},
    {"kill", no_argument, NULL, 'k'},
    {"conf-file", required_argument, NULL, 'c'},
    {"pid-file", required_argument, NULL, 'p'},
    {"log-file", required_argument, NULL, 'l'},
    {NULL, 0, NULL, 0}
  };

  const char *config_file = NULL;	/* The name of the configuration file
					   (or NULL for none). */
  const char *pid_file = NULL;	/* The name of the pid file (or NULL for none). */
  const char *log_file = NULL;	/* The name of the log file (or NULL for none). */

  program_name = argv[0];	/* Set the program name. The name is the name of the 
				   file which was executed i.e. it could be the name
				   of the executable or a symlink. */

  /* Parse options supplied on the command line. */
  do
    {
      next_option = getopt_long (argc, argv, short_options,
				 long_options, NULL);
      switch (next_option)
	{
	case 'h':		/* -h or --help */
	  print_usage (stdout, EXIT_SUCCESS);

	case 'v':		/* -v or --verbose */
	  verbose_mode = true;
	  break;

	case 'V':		/* -V or --version */
	  /**
	   * @bug \c --version prints usage instead of program version.
	   * @todo Replace with print_version which belongs in sp_initialize.c.
	   *       This requires also a variable or \c #define to hold the program version.
	   */
	  print_usage (stdout, EXIT_SUCCESS);
	  break;

	case 'd':		/* -d or --daemon */
	  daemon_mode = true;
	  break;

	case 'k':               /* -k or --kill */
	  /**
	   * @bug \c --kill prints usage instead of killing a running instance.
	   * @todo Replace with a function that kills the running daemon if a
	   *       pid-file was specified. Otherwise returns an error saying
	   *       that that a pid-file was not specified.
	   */
	  print_usage (stdout, EXIT_SUCCESS);
	  break;

	case 'c':		/* -c, --conf-file=FILE */
	  config_file = optarg;
	  break;

	case 'p':		/* -p, --pid-file=FILE */
	  pid_file = optarg;
	  break;

	case 'l':		/* -l, --log-file=FILE */
	  log_file = optarg;
	  break;

	case '?':		/* The user specified an invalid option.  */
	  print_usage (stderr, EXIT_FAILURE);

	case -1:		/* Finished with parsing options.  */
	  break;

	default:		/* Something unexpected happened.  */
	  abort ();
	}
    }
  while (next_option != -1);


  /* main.c - PROGRAM INITIALIZATION */

  /* Report program status to STREAM before calling daemon(). */
  if (verbose_mode)
    {
      printf (_("Running in verbose mode.\n"));
      if (config_file != NULL)
	{
	  printf (_("The configuration file name is %s.\n"), config_file);
	}
      if (pid_file != NULL)
	{
	  printf (_("The pid file name is %s.\n"), pid_file);
	}
      if (log_file != NULL)
	{
	  printf (_("The log file name is %s.\n"), log_file);
	}
      if (daemon_mode)
	{
	  printf (_("Running in daemon mode.\n"));
	}
    }

  /* Call daemon() to fork into background. */
  if (daemon_mode)
    {
      if (verbose_mode)
	{
	  printf (_("Calling daemon () to fork into background.\n"));
	}

      /* Handle the return value of daemon(). */
      switch (daemon (0, 0))
	{
	case 0:
	  {
	    if (log_file != NULL)
	      {
		if ((open_log_file (log_file)) == -1)
		  {
		    exit (EXIT_FAILURE);
		  }
		else
		  {
		    write_log_message (_("Smokeparrot daemon started"));
		  }
	      }

	    /**
	     * @todo After succesfully calling \c daemon() open and lock the pid
	     * file if specified and set up the SIGHUP handler. See 
	     * commented-out sections in sp_initialize.c.
	     **/

	    break;
	  }

	default:
	  {
	    /**
	     * @todo Write code to analyze the \c errno that \c daemon() got 
	     * from \c fork() or \c setsid().
	     **/
	    if (verbose_mode)
	      {
		/**
		 * @todo Use the code that analyzes \c errno and include the 
		 * name in the error message to STREAM.
		 **/
		write_log_message (_("Failed to become daemon."));
	      }
	    exit (EXIT_FAILURE);
	  }
	}
    }
  else
    /* Set logging when running in foreground. */
    {
      write_log_message (_("Running in foreground."));
      if (log_file != NULL)
	{
	  write_log_message (_("Logging further messages to file %s."),
			     log_file);
	  if ((open_log_file (log_file)) == -1)
	    {
	      write_log_message (_("Opening the log file failed."));
	      exit (EXIT_FAILURE);
	    }
	}

      else
	{
	  write_log_message (_("Logging to standard output"));
	}
    }


  /* main.c - MAIN PROGRAM */
  if (verbose_mode)
    {
      write_log_message (_("Entering the program main section."));
    }

  if (verbose_mode)
    {
      write_log_message (_("Exiting the program."));
    }
  exit (EXIT_SUCCESS);
}




/*   for (;;) */
/*     { */
/*       if (hup_signal_received != 0) */
/* 	{ */
/* 	  hup_signal_received = 0; */
/* 	  if ((CloseLogFile ()) == -1) */
/* 	    { */
/* 	      WriteLogMessage ("Could not close log file properly."); */
/* 	    } */
/* 	  else */
/* 	    { */
/* 	      OpenLogFile (LOG_FILE); */
/* 	    } */

/* 	} */
/*       sleep (30); */
/*       /\* CloseLogFile (); *\/ */
/*       /\* exit (EXIT_SUCCESS); *\/ */
/*     } */
/* } */
