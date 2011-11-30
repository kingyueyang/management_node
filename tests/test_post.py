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
    conn = httplib.HTTPConnection(url)
    conn.request(method, path)
    rc = conn.getresponse()
    print rc.status, rc.reason

if __name__ == '__main__':
    get('10.10.140.215:8888', 'GET', '/get')
