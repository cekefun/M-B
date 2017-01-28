#!/bin/bash
qmake Parser.pro
make
cd bin
./Parser
