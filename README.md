# rssfeed

Minimal rss feed generator for your HTML blogs.

## Usage

```bash
$ rssfeed blog.html

# index.xml contains the rss feed
```

## Configuration

rssfeed extracts blog information from `config.rss` file.
Example config file:

```bash
Title "Tanmay's blog"
URL https://tanmay.app/notablog
Description "Tanmay's not a blog"
RSS https://tanmay.app/notablog/index.xml
Language en
```
