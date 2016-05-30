#!/bin/bash

message=$1

spr=`echo $message | aspell list -l pl`
gw=""
if [ "$spr" = "$gw" ]
	then
		echo "$message jest poprawnym słowem w języku polskim"
	else 
		echo "$message nie jest poprawnym słowem w języku polskim"
fi

