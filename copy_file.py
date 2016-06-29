"""
copy files to corresponding dirs wrt indri_home
"""

import os
import json
import sys
import re
import argparse
import codecs
import shutil

def get_files(src_dir):
    files = []
    for f in os.walk(src_dir).next()[2]:
        m = re.search("sample$",f):
        if m is None:
            files.append(os.path.join(src_dir,f))
    return files

def do_copy(files,dest_dir):
    for f in files:
        print "from %s to %s" %(f,dest_dir)
        #shutil.copy(f,dest_dir)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("indri_home")
    args=parser.parse_args()
    code_home = os.path.split(__file__)[1]
    src_home = os.path.join(code_home,"src")
    src_dest = os.path.join(args.indri_home,"src")
    include_home = os.path.join(code_home,"include/indri")
    include_dest = os.path.join(indri_home,"include/indri")
    src_files = get_files(src_home)
    include_files = get_files(include_home)

    do_copy(src_files,src_dest)
    do_copy(include_files,include_dest)


if __name__=="__main__":
    main()

