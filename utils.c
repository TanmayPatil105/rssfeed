/*
 * utils.c
 */

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void
utils_throw_error (char *message)
{
  if (message)
    fprintf (stderr, "rssfeed: %s\n", message);
  else
    fprintf (stderr, "rssfeed: %s\n", strerror(errno));

  exit (EXIT_FAILURE);
}
