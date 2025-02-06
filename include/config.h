/*
 * config.h
 */

#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
  char *title;       /* Title of the blog */
  char *url;         /* URL of the blog */
  char *description; /* Description of the blog */
  char *link;        /* Link to the RSS feed */

  char *lang;        /* Primary language of the blog */
} Config;


Config *config_read (char   *file);
void    config_free (Config *config);

#endif
