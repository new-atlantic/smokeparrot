/**
 * @file sp_signals.c
 * @brief Signal handling for smokeparrot.
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

#include <signal.h>
#include <unistd.h>

#include "sp_signals.h"


/* GLOBAL VARIABLES */

/**
 * @brief The signal handler sets a flag when SIGHUP is received.
**/
volatile sig_atomic_t hup_signal_received = 0;


/* FUNCTION PROTOTYPES */

/**
 * @brief Registers a new handler for SIGHUP.
 *
 * @param received_signal The identifier of the signal.
 **/
static void sighup_handler (int received_signal);

/* FUNCTION BODIES */

static void
sighup_handler (int received_signal)
{
  /**
   * @todo Implement the functionality of the \c SIGHUP handler.
   **/
  hup_signal_received = 1;
}

int
setup_signal_handling(void)
{
  struct sigaction signal_action;

  /* Register new handles for SIGHUP. */
  sigemptyset (&signal_action.sa_mask);
  signal_action.sa_flags = SA_RESTART;
  signal_action.sa_handler = sighup_handler;

  if (sigaction (SIGHUP, &signal_action, NULL) == -1)
    {
      return -1;
    }

  return 0;
}
