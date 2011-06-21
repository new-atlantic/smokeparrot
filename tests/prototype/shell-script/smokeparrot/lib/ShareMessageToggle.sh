#!/bin/sh
# Change the share status of a smokeparrot message.

MESSAGE_NAME=$1
PREFIX="/smokeparrot"
MESSAGE_STORE="$PREFIX/messages/"
MESSAGE="$MESSAGE_STORE$MESSAGE_NAME"

if [ ! -f $MESSAGE ]
then
	echo "The message does not exist."
else
	if [ $(/bin/sed -n '5q4p' "$MESSAGE") == "SHARE" ]
	then
		/bin/sed -i 's/SHARE/NOSHARE/' "$MESSAGE"
	else
		/bin/sed -i 's/NOSHARE/SHARE/' "$MESSAGE"
	fi
fi
