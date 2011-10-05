/* main.c */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "sp_daemon.h"

extern int Daemonize (void);
extern int OpenLogFile (const char *logfile_name);
extern int CloseLogFile (void);
extern void WriteLogMessage (const char *format, ...);


volatile sig_atomic_t hup_signal_received = 0;
const char *LOG_FILE = "/tmp/smokeparrot.log";

int
main (void)
{

  /* process id */
  pid_t daemon_pid;

  /* fork () to daemonize */
  switch (daemon_pid = fork ())
    {

    case -1:
      /* if fork () failed */
      {
	exit (EXIT_FAILURE);
      }

    case 0:
      /* daemonize child process */
      {

	if (Daemonize () != 0)
	  {
	    exit (EXIT_FAILURE);
	  }

	break;
      }

    default:
      /* parent process exits here */
      {
	_exit (EXIT_SUCCESS);
      }
    }


  /* daemon continues here with an infinite while loop */
  for (;;)
    {
      if (hup_signal_received != 0)
	{
	  hup_signal_received = 0;
	  if ((CloseLogFile ()) == -1)
	    {
	      WriteLogMessage("Could not close log file properly.");
	    }
	  else 
	    {
	      (void) OpenLogFile (LOG_FILE);
	}
	  
	}
      (void) sleep (30);
      /* CloseLogFile (); */
      /* exit (EXIT_SUCCESS); */
    }
}
