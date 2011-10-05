#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>

#include "sp_daemon.h"

#define PID_FILE_BUFFER_SIZE 100

static void SigHupHandler (int signal);
static int CreatePIDFile (const char *pid_file);

extern const char *LOG_FILE;
/* static const char *CONFIG_FILE = "/tmp/ds.conf"; */
static FILE *log_file_stream;

extern volatile sig_atomic_t hup_signal_received;

int
Daemonize (void)
{

  int max_file_descriptors, file_descriptor;
  struct sigaction signal_action;

  sigemptyset (&signal_action.sa_mask);
  signal_action.sa_flags = SA_RESTART;
  signal_action.sa_handler = SigHupHandler;

  if (sigaction (SIGHUP, &signal_action, NULL) == -1)
    {
      return -1;
    }

  if (setsid () == -1)
    {
      return -1;
    }

  umask (027);
  chdir ("/");

  /* close file descriptors */

  max_file_descriptors = sysconf (_SC_OPEN_MAX);

  if (max_file_descriptors == -1)
    {
      max_file_descriptors = 8192;
    }

  for (file_descriptor = 0; file_descriptor < max_file_descriptors;
       file_descriptor++)
    close (file_descriptor);

  close (STDIN_FILENO);

  file_descriptor = open ("/dev/null", O_RDWR);

  if (file_descriptor != STDIN_FILENO)
    {
      return -1;
    }

  if (dup2 (STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
    {
      return -1;
    }

  if (dup2 (STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
    {
      return -1;
    }

  if (CreatePIDFile ("/tmp/smokeparrot.pid") == -1)
    {
      return -1;
    }

  if((OpenLogFile (LOG_FILE)) == -1)
    {
      return -1;
    }

  return 0;

}

static int
CreatePIDFile (const char *pid_file)
{
  int file_descriptor;
  char pid_file_buffer[PID_FILE_BUFFER_SIZE];
  struct flock file_lock;

  file_descriptor = open (pid_file, O_RDWR | O_CREAT, 00600);

  file_lock.l_type = F_WRLCK;
  file_lock.l_whence = SEEK_SET;
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

static void
SigHupHandler (int signal)
{
  WriteLogMessage ("Received SIGHUP");
  hup_signal_received = 1;
}

int
OpenLogFile (const char *log_file_name)
{
  mode_t mask;
  mask = umask (0077);
  log_file_stream = fopen (log_file_name, "a");

  if (log_file_stream == NULL)
    {
      return -1;
    }

  umask (mask);
  setbuf (log_file_stream, NULL);

  WriteLogMessage ("Log file opened succesfully");

  return 0;
}

int
CloseLogFile (void)
{
  WriteLogMessage ("Closing log file");
  if (fclose (log_file_stream) != 0)
    {
      return -1;
    }

  return 0;
}

void
WriteLogMessage (const char *format, ...)
{
  va_list argument_list;
  /* const char *TIMESTAMP_FORMAT = "%F %X"; */
#define TIMESTAMP_BUFFER_SIZE sizeof("YYYY-MM-DD HH:MM:SS")
  char timestamp[TIMESTAMP_BUFFER_SIZE];
  time_t t;
  struct tm *local_time;

  t = time (NULL);
  local_time = localtime (&t);

  if (local_time == NULL
      || strftime (timestamp, TIMESTAMP_BUFFER_SIZE,
		   "%F %X" /* TIMESTAMP_FORMAT */ , local_time) == 0)
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
