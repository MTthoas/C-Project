gcc -g trying.c -o trying.c_test `mysql_config --cflags --libs` 
gcc -g `pkg-config --cflags gtk+-3.0` main.c curlPages.c -o helloworld  `pkg-config --libs gtk+-3.0` -lcurl
./helloworld
# ./trying.c_test

