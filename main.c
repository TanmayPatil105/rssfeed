/*
 * main.c
 */

#include "config.h"
#include "html.h"
#include "utils.h"
#include "xml.h"

#include <stdio.h>
#include <string.h>


static char *
form_html_link (char *url,
                char *file)
{
  char link[100];

  strcpy (link, url);
  strcpy (link, "/");
  strcat (link, file);

  return strdup (link);
}

int
main (int   argc,
      char *argv[])
{
  Html *html;
  Config *config;

  if (argc < 2)
    {
      utils_throw_error ("Not enough arguments");
    }

  config = config_read (NULL);

  html = html_read_from_file (argv[1]);

  html->link = form_html_link (config->link, argv[1]);

  xml_dump (config, html);

  config_free (config);
  html_free (html);
  return 0;
}

