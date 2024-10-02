/*
 * config.c
 */

#include "config.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Config *
config_new ()
{
  Config *config;

  config = malloc (sizeof (Config));

  if (config == NULL)
    utils_throw_error ("Not enough memory");

  return config;
}

void
config_free (Config *config)
{
  if (config->title)
    free (config->title);
  if (config->url)
    free (config->url);
  if (config->description)
    free (config->description);
  if (config->link)
    free (config->link);
  if (config->lang)
    free (config->lang);
}

static char *
parse_value (char *line)
{
  char *value;
  size_t len;
  char *space, *newline;

  /* FIXME: loop until you don't find non-space character */
  space = strchr (line, ' ');
  newline = strchr (space, '\n');

  len = newline - space;
  value = malloc (sizeof (char) * (len));

  strncpy (value, space + 1, len - 1);
  value[len - 1] = '\0';

  return value;
}

Config *
config_read (char *file)
{
  Config *config;
  FILE *fptr;
  size_t len = 0;
  char *line = NULL;

  config = config_new ();

  if (file == NULL)
    fptr = fopen ("./config.rss", "r");
  else
    fptr = fopen (file, "r");

  if (fptr == NULL)
    utils_throw_error ("Provide a config file");

  while (getline (&line, &len, fptr) != -1)
    {
      if ((strncmp (line, "Title", 5)) == 0)
        config->title = parse_value (line);
      else if ((strncmp (line, "URL", 3)) == 0)
        config->url = parse_value (line);
      else if ((strncmp (line, "Description", 11)) == 0)
        config->description = parse_value (line);
      else if ((strncmp (line, "RSS", 3)) == 0)
        config->link = parse_value (line);
      else if ((strncmp (line, "Language", 8)) == 0)
        config->lang = parse_value (line);
    }

  return config;
}
