#!/bin/bash
path=$(pwd);
logname="mdubuntu"
cd $(pwd)/sampl*/tirtos/certs/cc3200/
make clean && ~/ti/xdctools_*/gmake all;
cd ../../subscribe_publish_sample/cc3200/
make clean && ~/ti/xdctools_*/gmake all;
echo "Done Configuring and building output file...";
cd ../../../../
sudo chmod -R 777 ./*
sudo mkdir -p $path/Build

echo "Just check the output files are created in Build folder...!";

/home/$logname/ti/ccsv6/utils/tiobj2bin/tiobj2bin "$path/samples/tirtos/subscribe_publish_sample/cc3200/subscribe_publish_sample.out" "$path/HIVEPIE-30121/subscribe_publish_sample.bin" "/home/$logname/ti/ccsv6/tools/compiler/c6000_7.4.18/bin/ofd6x" "/home/$logname/ti/ccsv6/tools/compiler/c6000_7.4.18/bin/hex6x" "/home/$logname/ti/ccsv6/utils/tiobj2bin/mkhex4bin";

/home/$logname/ti/ccsv6/utils/tiobj2bin/tiobj2bin "$path/samples/tirtos/certs/cc3200/certflasher.out" "$path/HIVEPIE-30121/certflasher.bin" "/home/$logname/ti/ccsv6/tools/compiler/c6000_7.4.18/bin/ofd6x" "/home/$logname/ti/ccsv6/tools/compiler/c6000_7.4.18/bin/hex6x" "/home/$logname/ti/ccsv6/utils/tiobj2bin/mkhex4bin"


sudo cp samples/tirtos/subscribe_publish_sample/cc3200/subscribe_publish_sample.out ./HIVEPIE-30121/
sudo cp samples/tirtos/certs/cc3200/certflasher.out ./HIVEPIE-30121/
sudo chmod -R 777 ./*

