#!/bin/sh
# Create a Smokeparrot message.

PREFIX="/smokeparrot"
MESSAGE_STORE="$PREFIX/messages/"

SENDER_ADDRESS=$($PREFIX/lib/GetAddress.sh)
MESSAGE_BODY="$1"
SENDER_NAME="$2"

SHARE_STATUS="SHARE"
OWNERSHIP="OWN"

TIMESTAMP=$(date +%s)
MESSAGE_CREATED="$TIMESTAMP"
MESSAGE_RECEIVED="$TIMESTAMP"
HASH=$(echo "$MESSAGE_CREATED$SENDER_ADDRESS$MESSAGE_BODY" | md5sum | awk '{ print $1 }')
MESSAGE_NAME="$MESSAGE_RECEIVED-$HASH.txt"
MESSAGE="$MESSAGE_STORE/$MESSAGE_NAME"

touch "$MESSAGE"
echo $SENDER_ADDRESS >> $MESSAGE
echo $MESSAGE_CREATED >> $MESSAGE
echo $HASH >> $MESSAGE
echo $SHARE_STATUS >> $MESSAGE
echo $OWNERSHIP >> $MESSAGE
echo 0 >> $MESSAGE
echo "" >> $MESSAGE
echo "" >> $MESSAGE
echo "" >> $MESSAGE
echo $SENDER_NAME >> $MESSAGE
echo "" >> $MESSAGE
echo $MESSAGE_BODY >> $MESSAGE
