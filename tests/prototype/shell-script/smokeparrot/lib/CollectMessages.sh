#!/bin/sh
# Collect shared messages.
# TODO: This script should be adapted to be run in GetRemoteMessages before ProcessReceivedMessages.

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
