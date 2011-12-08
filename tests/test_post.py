#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
    <+ MODULE_NAME +>

    <+ DESCRIPTION +>

    Licensed under the <+ LICENSE +> license, see <+ X +> for more details etc.
    Copyright by yueyang
"""

#import urllib2

#def post(url, string):
    #c = urllib2.Request(url, string)
    #c.add_header('Content-Type', 'application/xml')
    #resopne = None
    #try:
        #resopne = urllib2.urlopen(c)
    #except urllib2.URLError:
        #print 'POST error'

    #if resopne:
        #print resopne.read()

#if __name__ == '__main__':
    #post('10.10.140.215:8888/get', '<?xml version="1.0"?> <grant> <id>qwert</id> <type>1</type> </grant>')

import httplib
import urllib

def get(url, method, path):
    conn = None
    conn = httplib.HTTPConnection(url)
    params = '<grant> <id>qwert</id> <type>1</type> </grant>\n'
    #headers = {"Content-type": "application/xml", "Accept": "text/plain"}
    try:
        conn.request(method, path, params)
    except:
        print "get: socket error"
        return
    try:
        rc = conn.getresponse()
    except:
        print "error"
        return

    buf = rc.read()
    print rc.status, rc.reason, buf

if __name__ == '__main__':
    print "POST: /post"
    get('10.10.140.215:8888', 'POST', '/post')

    #print "POST: /get"
    #get('10.10.140.215:8888', 'POST', '/get')
    #print "\n"

    #print "GET: /xxx"
    #get('10.10.140.215:8888', 'GET', '/xxx')

