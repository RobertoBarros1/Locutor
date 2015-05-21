#!/bin/bash

a=`pwd`
 
a=$(aoss ./oss config2.txt)

result1=${a/.*}

if [ -z $a ];
then 
	echo "Erro porfavor fale novamente!!"

elif [ $result1 -ge 150 ];
then
	#stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo 
	#echo "m" > /dev/ttyACM0
	#x-terminal-emulator -e minicom
	echo $result1
	/home/roberto/Desktop/./uart
	echo "Bem vindo Roberto"
else
	echo "Impostor"
	echo $result1 	 
fi
