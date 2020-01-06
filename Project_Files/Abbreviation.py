##command line: curl https://en.wikipedia.org/wiki/List_of_Hebrew_abbreviations > abbrev.txt


#!/usr/bin/env python3
import re

pat = re.compile(r'li>(.+),(.+)\(.+</li>') #,flags=re.DOTALL)
data = open("abbrev.txt").read()
if data:
    table = re.findall(pat, data)
    for row in table:
        print(row[0],"|",row[1])
