/*
 * html.c
 */

#include "html.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>


Html *
html_new ()
{
  Html *html;

  html = malloc (sizeof (Html));

  if (html == NULL)
    utils_throw_error ("Not enough memory");

  html->link = NULL;
  html->prev = NULL;

  return html;
}

void
html_free (Html *html)
{
  if (html->title)
    free (html->title);
  if (html->desc)
    free (html->desc);
  if (html->pubdate)
    free (html->pubdate);
}

static void
html_parse (FILE *fptr,
            char *title,
            char *desc)
{
  bool is_title = false;
  bool is_body = false;
  int title_len = 0;
  int body_len = 0;
  char line[1000];

  while (fgets (line, sizeof(line), fptr) != NULL)
    {
      char *ptr = line;

      while (*ptr != '\0')
        {
          if (strncmp (ptr, "<title>", 7) == 0)
            {
              is_title = true;
              ptr += 7;
            }
          else if (strncmp (ptr, "</title>", 8) == 0)
            {
              is_title = false;
              title[title_len] = '\0';
              ptr += 8;
            }
          else if (strncmp (ptr, "<body>", 6) == 0)
            {
              is_body = true;
              ptr += 6;
            }
          else if (strncmp (ptr, "</body>", 7) == 0)
            {
              is_body = false;
              desc[body_len] = '\0';
              ptr += 7;
            }
          else if (is_title && title_len < MAX_TITLE_LEN - 1)
            {
              title[title_len++] = *ptr++;
            }
          else if (is_body && body_len < MAX_DESC_LEN - 1)
            {
                desc[body_len++] = *ptr++;
            }
          else
            {
              ptr += 1;
            }
         }
     }
}

static char *
get_date (char *file)
{
  struct stat fs;
  time_t crt;
  struct tm *tm;
  char date[100];

  if (stat (file, &fs) != 0)
    utils_throw_error ("Unable to stat file");

  crt = fs.st_mtime;

  tm = localtime (&crt);

  strftime (date, 100, "%a, %d %b %Y %H:%M:%S +0530", tm);

  return strdup (date);
}

Html *
html_read_from_file (char *file)
{
  Html *html = NULL;
  FILE *fptr = NULL;
  char title[MAX_TITLE_LEN] = { '\0' };
  char desc[MAX_DESC_LEN] = { '\0' };

  fptr = fopen (file, "r");

  if (fptr == NULL)
    utils_throw_error ("Provide a valid HTML file");

  html_parse (fptr, title, desc);

  html = html_new();
  html->title = strdup (title);
  html->desc = strdup (desc);
  html->pubdate = get_date (file);

  return html;
}
