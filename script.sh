gcc -g `pkg-config --cflags gtk+-3.0` main.c curlPages.c transition.c database.c -o helloworld  `pkg-config --libs gtk+-3.0` `mysql_config --cflags --libs`  -lcurl
./helloworld
# ./trying.c_test

