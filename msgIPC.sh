#!/bin/bash

echo -e -n "Podaj komunikat do wysłania: "
read message

sciezka="./ipcmd/bin/ipcmd"
ID=$($sciezka msgget)

dzien=$(date +%u)

if [ $dzien == 5 ] || [ $dzien == 6 ] || [ $dzien == 7 ]
then
	if [[ "${message:0:1}" = [a-zA-Z] ]]
	then
		$sciezka msgsnd -q $ID $message
		echo -e -n "Otrzymany komunikat: "
		$sciezka msgrcv -q $ID
		echo -e -n "\n\n"
		./aspell.sh $message
	fi
else
	echo -e -n "Nie ma weekendu więc nie odczytam wiadomości.\n"
fi

