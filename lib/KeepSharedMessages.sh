#!/bin/sh
# Delete messages from the incoming message queue if they are not meant to be shared.

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_QUEUE=$SMOKEPARROT_PATH/queue/

MESSAGE_LIST=$(ls -l $MESSAGE_QUEUE | awk '{ print $9 }')
SHARED_MESSAGE_LIST=""
for MESSAGE_NAME in $MESSAGE_LIST;
do
    if [ ! $(/bin/sed -n '5q4p' $MESSAGE_QUEUE$MESSAGE_NAME) == "SHARE" ]
    then
	rm $MESSAGE_QUEUE$MESSAGE_NAME
    fi
done

