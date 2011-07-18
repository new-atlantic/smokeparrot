#!/bin/sh
# Deletes hidden messages.

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_STORE=$SMOKEPARROT_PATH/messages/

MESSAGE_LIST=$(ls -l $MESSAGE_STORE | awk '{ print $9 }' )


for MESSAGE_NAME in $MESSAGE_LIST; do
    if [ $(/bin/sed -n '8q7p' "$MESSAGE_STORE$MESSAGE_NAME") == "HIDDEN" ]; then
	HASH=$(/bin/sed -n '3p' "$MESSAGE_STORE$MESSAGE_NAME")
	echo "$HASH" >> $SMOKEPARROT_PATH/deleted_messages
	/bin/rm $MESSAGE_STORE$MESSAGE_NAME
    fi
done
	