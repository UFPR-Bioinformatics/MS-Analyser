#!/bin/bash

LD_LIBRARY_PATH=$(dirname $(readlink -f $0))/LIBS $(dirname $(readlink -f $0))/MS-Analyser &> /dev/null
