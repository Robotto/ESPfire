#!/usr/bin/env python
import feedparser
import time
odin_rss_url = "http://odin.dk/" \
                      "RSS/RSS.aspx?beredskabsID=1110"
feed = feedparser.parse( odin_rss_url )

entries = []
entries.extend( feed[ "items" ] )

for entry in entries:
    if u"Station: Aarhus" in entry.summary:
        print entry.summary[15:-16], "@" , time.strftime('%H:%M:%S d.%d/%m-%Y', entry.published_parsed)
        break #only first entry needed..

