#!/bin/sh
# Collect messages for sending.

PREFIX="/smokeparrot"
MESSAGE_STORE="$PREFIX/messages/"
MESSAGE_LIST=$(ls -l $MESSAGE_STORE | awk '{ print $9 }')
SHARED_MESSAGE_LIST=""
for MESSAGE_NAME in $MESSAGE_LIST;
do
	if [ $(/bin/sed -n '5q4p' "$MESSAGE_STORE$MESSAGE_NAME") == "SHARE" ]
	then
		SHARED_MESSAGE_LIST="$SHARED_MESSAGE_LIST$MESSAGE_NAME "
	fi
done

echo $SHARED_MESSAGE_LIST
