# rssfeed

Minimal rss feed generator for your HTML blogs.

Example RSS feed generated using rssfeed: [https://tanmay.app/notablog/index.xml](https://tanmay.app/notablog/index.xml)

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
