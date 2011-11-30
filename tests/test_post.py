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

import re,sys,os,urllib,time
import datetime,socket

def post(url, c_type, header, string):
    c = urllib2.Request(url, string)
    c.add_header(c_type, header)
    try:
        resopne = urllib2.urlopen(c)
    except urllib2.URLError:
        print 'POST error'
    #data = c.read()
    #print data
    #print dir(c)

if __name__ == '__main__':
    post('http://10.10.140.215:8888/post', 'Content-Type',
            'POST', 'PING\n')

