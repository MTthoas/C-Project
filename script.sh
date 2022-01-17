!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o helloworld main.c `pkg-config --libs gtk+-3.0`
./helloworld


