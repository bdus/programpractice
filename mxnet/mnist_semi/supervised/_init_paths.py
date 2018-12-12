#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 12 23:02:10 2018

@author: bdus
"""

import os.path as osp
import sys

def add_path(path):
    if path not in sys.path:
        sys.path.insert(0, path)

this_dir = osp.dirname(__file__)
lib_path = osp.join(this_dir, '..', 'lib')
#data_path = osp.join(this_dir, '..''data')
add_path(lib_path)
#add_path(data_path)