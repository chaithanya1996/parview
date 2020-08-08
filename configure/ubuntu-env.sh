#!/bin/bash

apt update
apt install -y -V ca-certificates lsb-release wget
if [ $(lsb_release --codename --short) = "stretch" ]; then
   tee /etc/apt/sources.list.d/backports.list <<APT_LINE
deb http://deb.debian.org/debian $(lsb_release --codename --short)-backports main
APT_LINE
fi
wget https://apache.bintray.com/arrow/$(lsb_release --id --short | tr 'A-Z' 'a-z')/apache-arrow-archive-keyring-latest-$(lsb_release --codename --short).deb
apt install -y -V ./apache-arrow-archive-keyring-latest-$(lsb_release --codename --short).deb
apt update

apt install -y -V libarrow-dev # For C++
apt install -y -V libarrow-dataset-dev # For Arrow Dataset C++
apt install -y -V libarrow-flight-dev # For Flight C++
apt install -y -V libplasma-dev # For Plasma C++
apt install -y -V libgandiva-dev # For Gandiva C++
apt install -y -V libparquet-dev # For Apache Parquet C++
