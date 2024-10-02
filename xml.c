/*
 * xml.c
 */

#include "xml.h"

#include <stdio.h>

#define XML_FILE "index.xml"

static void
dump_header (FILE *fptr)
{
  char template[200];

  sprintf (template,
    "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n"
    "<rss version=\"2.0\" xmlns:atom=\"http://www.w3.org/2005/Atom\">\n"
    "\t<channel>\n");

  fprintf (fptr, "%s", template);
}

static void
dump_footer (FILE *fptr)
{
  char template[100];

  sprintf (template,
    "\t</channel>\n"
    "</rss>");

  fprintf (fptr, "%s", template);
}

static void
dump_channel_value (FILE *fptr,
                    char *value,
                    char *start_tag,
                    char *end_tag)
{
  char template[200];

  sprintf (template,
    "\t\t%s%s%s\n",
    start_tag, value, end_tag);

  fprintf (fptr, "%s", template);
}

static void
dump_channel_rss_link (FILE *fptr,
                       char *link)
{
  char template[200];

  sprintf (template,
    "\t\t<atom:link href=\"%s\" rel=\"self\" type=\"application/rss+xml\" />\n",
      link);

  fprintf (fptr, "%s", template);
}

static void
dump_blog_header (FILE *fptr)
{
  char template[20];

  sprintf (template,
    "\t\t<item>\n");

  fprintf (fptr, "%s", template);
}

static void
dump_blog_footer (FILE *fptr)
{
  char template[20];

  sprintf (template,
    "\t\t</item>\n");

  fprintf (fptr, "%s", template);
}

static void
dump_blog_description (FILE *fptr,
                       char *desc)
{
  fprintf (fptr, "\t\t\t<description>\n");

  fprintf (fptr, "%s\n", desc);

  fprintf (fptr, "\t\t\t</description>\n");
}

static void
dump_blog_value (FILE *fptr,
                 char *value,
                 char *start_tag,
                 char *end_tag)
{
  char template[200];

  sprintf (template,
    "\t\t\t%s%s%s\n",
    start_tag, value, end_tag);

  fprintf (fptr, "%s", template);
}

static void
dump_blog_item (FILE *fptr,
                Html *html)
{
  dump_blog_header (fptr);

  if (html->title)
    dump_blog_value (fptr, html->title, "<title>", "</title>");

  if (html->link)
    dump_blog_value (fptr, html->link, "<link>", "</link>");

  if (html->pubdate)
    dump_blog_value (fptr, html->pubdate, "<pubDate>", "</pubDate>");

  if (html->desc)
    dump_blog_description (fptr, html->desc);

  dump_blog_footer (fptr);
}

void
xml_dump (Config *config,
          Html   *html)
{
  FILE *fptr;

  fptr = fopen (XML_FILE, "w");

  dump_header (fptr);

  if (config->title)
    dump_channel_value (fptr, config->title, "<title>", "</title>");

  if (config->url)
    dump_channel_value (fptr, config->url, "<link>", "</link>");

  if (config->description)
    dump_channel_value (fptr, config->description, "<description>", "</description>");

  if (config->link)
    dump_channel_rss_link (fptr, config->link);

  if (config->lang)
    dump_channel_value (fptr, config->lang, "<language>", "</language>");

  dump_blog_item (fptr, html);

  dump_footer (fptr);
}
