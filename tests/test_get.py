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

import httplib

def get(url, method, path):
    conn = None
    conn = httplib.HTTPConnection(url)
    try:
        conn.request(method, path)
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
    print "GET: /get"
    get('10.10.140.215:8888', 'GET', '/get')
    print "\n"

    print "POST: /get"
    get('10.10.140.215:8888', 'POST', '/get')
    print "\n"

    print "GET: /xxx"
    get('10.10.140.215:8888', 'GET', '/xxx')

