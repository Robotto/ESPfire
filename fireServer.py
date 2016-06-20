#!/usr/bin/env python
import feedparser

import time
#import datetime
#from dateutil.parser import parse #to handle timezone offset.

import socket
from IPy import IP

#get the feed and parse it:
def getNotifications():
    try:
        odin_rss_url = "http://odin.dk/" \
                      	"RSS/RSS.aspx?beredskabsID=1110"
        feed = feedparser.parse( odin_rss_url )

        entries = []
        entries.extend( feed[ "items" ] )

        for entry in entries:
            if u"Station: Aarhus" in entry.summary:
                #print entry.summary[15:-16], "@" , time.strftime('%H:%M:%S d.%d/%m-%Y', entry.published_parsed)
                return entry.summary, entry.published_parsed
                break #only first entry needed..

    except Exception as e:
        print "hmm.. It looks like there was a network timeout: " + str(e)

    return null

print time.ctime(),"startup!"

TCP_IP = '62.212.66.171'
TCP_PORT = 666
BUFFER_SIZE = 20  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) #make socket reuseable, for debugging (enables you to rerun the program before the socket has timed out)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

print 'get the fire..'
print
event, timestamp = getNotifications()
lastTime = int(time.time()) #Update time
print
print 'Done.. Opening TCP port', TCP_PORT

while True:
    try:
        conn, addr = s.accept()
        print time.ctime(),'Connection from:', addr
        print 'Refresh...'
        event, timestamp = getNotifications()
        txString = str(event[15:-16])+'\r'+time.strftime('%d/%m-%Y', timestamp)+'\r'+time.strftime('%H:%M:%S', timestamp)+'\r'
        conn.send(txString)#+'\n')  # echo
        print 'TX:\r\n', txString.replace('\r','\r\n')
        print 'Client disconnected.'
        print '--------------------------'
        conn.close()
    except Exception as e:
        #print "hmm.. It looks like there was an error: " + str(e)
        print 'Client disconnected... :',str(e)
        print '--------------------------'
        conn.close()
