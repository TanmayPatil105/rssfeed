/*
 * file.h
 */

#ifndef HTML_H
#define HTML_H

typedef struct Html
{
  char *title;   /* Title of the blog */
  char *desc;    /* short 100 line description */

  char *link;    /* Link to the web page */

  char *pubdate; /* The data blog was published/created */

  /* This is a reverse linked list
   * storing blogs in reverse order of publication */
  struct Html *prev;
} Html;

Html *html_read_from_file (char *file);
void  html_free           (Html *html);

#endif
