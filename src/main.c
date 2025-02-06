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
  strcat (link, "/");
  strcat (link, file);

  return strdup (link);
}

int
main (int   argc,
      char *argv[])
{
  Html *html;
  Html *list;
  Config *config;

  if (argc < 2)
    {
      utils_throw_error ("Not enough arguments");
    }

  config = config_read (NULL);

  html = html_read_from_file (argv[1]);
  html->link = form_html_link (config->url, argv[1]);
  list = html;

  for (int i = 2; i < argc; i++)
    {
      Html *prev;

      prev = html_read_from_file (argv[i]);
      prev->link = form_html_link (config->url, argv[i]);

      list->prev = prev;
      list = list->prev;
    }

  xml_dump (config, html);

  config_free (config);
  html_free (html);

  return 0;
}

