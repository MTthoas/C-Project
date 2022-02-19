gcc trying.c -o trying.c_test `mysql_config --cflags --libs` 
gcc `pkg-config --cflags gtk+-3.0`  -o helloworld main.c `pkg-config --libs gtk+-3.0` `mysql_config --cflags --libs` 
./helloworld
# ./trying.c_test

