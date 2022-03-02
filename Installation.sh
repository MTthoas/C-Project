apt-get update
apt install software-properties-common apt-transport-https curl
curl -sSl https://packages.microsoft.com/keys/microsoft.adc | sudo apt-key add
apt-key add microsoft.asc
cd /etc/apt/sources.list
nano /etc/apt/sources.list

    # Coller à la toute dernière ligne : 
    # deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main

apt-get update
apt-get install -y code
apt-get install gcc
apt-cache search libcurl | grep python
apt install python3-pycurl
apt install libcurl
apt install libcurl-dev
apt install libcurl4-openssl-dev
apt-get install libcurl4-gnutls-dev
apt-get install libcurl4-openssl-dev
apt-get install libcurl4-nss-dev
apt-get install libgtk3.0
apt-get install build-essential gnome-devel
apt-get install libgtk-3-dev
apt install git
apt install libmysqlclient15-dev
apt install mysql
apt-get install mysql-server
apt install default-libmysqlclient-dev

apt-get update



