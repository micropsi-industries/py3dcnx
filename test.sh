#!/bin/bash
export SOURCES="py3dcnx.c py3dcnx_hidapi.c"
gcc -shared -fPIC -I/usr/include/python2.7 $SOURCES -o py3dcnx.so -lhidapi-hidraw
python2.7 -c "import py3dcnx;py3dcnx.test()"
gcc -shared -fPIC -I/usr/include/python3.5 $SOURCES -o py3dcnx.so -lhidapi-hidraw
python3 -c "import py3dcnx;py3dcnx.test()"
