# -*- coding: utf-8 -*-
"""
Created on Mon Dec 21 17:45:11 2020

@author: VD
"""

import random

fhand=open('inp_graph.txt','w')

nodes=1000

fhand.write(f"1\n{nodes} 1\n")

for i in range(nodes):
    row=list()
    for j in range(nodes):
        if i==j:
            wt=0
        else:
            is_edge=random.randint(0,20);
            if is_edge==0:
                wt=999999
            else:
                wt=random.randint(1,999)
        row.append(wt)
    listToStr = ' '.join([str(elem) for elem in row])
    listToStr+='\n'
    fhand.write(listToStr)