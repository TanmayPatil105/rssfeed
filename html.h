/*
 * file.h
 */

#ifndef HTML_H
#define HTML_H

typedef struct
{
  char *title;   /* Title of the blog */
  char *desc;    /* short 100 line description */

  char *link;    /* Link to the web page */

  char *pubdate; /* The data blog was published/created */
} Html;

Html *html_read_from_file (char *file);
void  html_free           (Html *html);

#endif
