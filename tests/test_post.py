#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
    <+ MODULE_NAME +>
    TEST POST

    <+ DESCRIPTION +>
    post somethin to http server

    Licensed under the <+ LICENSE +> license, see <+ X +> for more details etc.
    Copyright by yueyang
"""

import urllib2
import httplib

def post(url, c_type, header, string):
    c = urllib2.Request(url, string)
    c.add_header(c_type, header)
    resopne = None
    try:
        resopne = urllib2.urlopen(c)
    except urllib2.URLError:
        print 'POST error'

    if resopne:
        print resopne.read()

def get(url, method, path):
    conn = None
    conn = httplib.HTTPConnection(url)
    try:
        conn.request(method, path)
    except:
        print "get: socket error"
        return
    rc = conn.getresponse()

    buf = rc.read()
    print rc.status, rc.reason, buf

if __name__ == '__main__':
    print "GET: /get"
    get('10.10.140.215:8888', 'GET', '/get')
    print "\n"

    print "POST: /get"
    get('10.10.140.215:8888', 'POST', '/get')
    print "\n"

    print "GET: /xxx"
    get('10.10.140.215:8888', 'GET', '/xxx')
