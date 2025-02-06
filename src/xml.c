/*
 * xml.c
 */

#include "xml.h"

#include <stdio.h>
#include <string.h>

#define XML_FILE "index.xml"

static void
xml_dump_header (FILE *fptr)
{
  char template[200];

  sprintf (template,
    "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n"
    "<rss version=\"2.0\" xmlns:atom=\"http://www.w3.org/2005/Atom\">\n"
    "\t<channel>\n");

  fprintf (fptr, "%s", template);
}

static void
xml_dump_footer (FILE *fptr)
{
  char template[100];

  sprintf (template,
    "\t</channel>\n"
    "</rss>");

  fprintf (fptr, "%s", template);
}

static void
xml_dump_channel_value (FILE *fptr,
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
xml_dump_channel_rss_link (FILE *fptr,
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
xml_dump_blog_footer (FILE *fptr)
{
  char template[20];

  sprintf (template,
    "\t\t</item>\n");

  fprintf (fptr, "%s", template);
}

enum
{
  CHAR_NEWLINE = 0,
  CHAR_LESS_THAN,
  CHAR_GREATER_THAN,
  CHAR_AMPERSAND,
  CHAR_DOUBLE_QUOTE,
  CHAR_SINGLE_QUOTE,
  N_CHARS
};

static struct {
  char c;
  char str[20];
} chars[N_CHARS] = {
  { '\n', "\n\t\t\t"}, /* newline formatting */
  { '<',  "&lt;" },
  { '>',  "&gt;" },
  { '&',  "&amp;" },
  { '"',  "&quot;" },
  { '\'', "&apos;" },
};

static inline unsigned int
get_char_index (char c)
{
  for (unsigned int i = 0; i < N_CHARS; i++)
    {
      if (c == chars[i].c)
        return i;
    }

  return N_CHARS;
}

static char *
replace_tags (char *desc)
{
  char chgd[MAX_DESC_LEN + 1000];
  char *ptr = chgd;

  while (*desc != '\0')
    {
       unsigned int index;

       index = get_char_index (*desc);

       if (index == N_CHARS)
         {
           *ptr++ = *desc;
         }
       else
        {
          char *str;

          str = chars[index].str;

          strcpy (ptr, str);

          ptr += strlen (str);
        }

      desc++;
    }

  *ptr = '\0';

  return strdup (chgd);
}

static void
xml_dump_blog_description (FILE *fptr,
                           char *desc)
{
  fprintf (fptr, "\t\t\t<description>\n");

  fprintf (fptr, "%s\n", replace_tags (desc));

  fprintf (fptr, "\t\t\t</description>\n");
}

static void
xml_dump_blog_value (FILE *fptr,
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
xml_dump_blog_item (FILE *fptr,
                    Html *html)
{
  dump_blog_header (fptr);

  if (html->title)
    xml_dump_blog_value (fptr, html->title, "<title>", "</title>");

  if (html->link)
    xml_dump_blog_value (fptr, html->link, "<link>", "</link>");

  if (html->pubdate)
    xml_dump_blog_value (fptr, html->pubdate, "<pubDate>", "</pubDate>");

  if (html->desc)
    xml_dump_blog_description (fptr, html->desc);

  xml_dump_blog_footer (fptr);
}

static void
xml_dump_config (FILE   *fptr,
                 Config *config)
{
  if (config->title)
    xml_dump_channel_value (fptr, config->title, "<title>", "</title>");

  if (config->url)
    xml_dump_channel_value (fptr, config->url, "<link>", "</link>");

  if (config->description)
    xml_dump_channel_value (fptr, config->description, "<description>", "</description>");

  if (config->link)
    xml_dump_channel_rss_link (fptr, config->link);

  if (config->lang)
    xml_dump_channel_value (fptr, config->lang, "<language>", "</language>");
}

void
xml_dump (Config *config,
          Html   *html)
{
  FILE *fptr;

  fptr = fopen (XML_FILE, "w");

  xml_dump_header (fptr);

  xml_dump_config (fptr, config);

  while (html != NULL)
    {
      xml_dump_blog_item (fptr, html);
      html = html->prev;
    }

  xml_dump_footer (fptr);
}
