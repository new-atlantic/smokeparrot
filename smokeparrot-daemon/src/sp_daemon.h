#ifndef SP_DAEMON_H
#define SP_DAEMON_H

int Daemonize (void);
int OpenLogFile (const char *logfile_name);
int CloseLogFile (void);
void WriteLogMessage (const char *format, ...);


#endif
