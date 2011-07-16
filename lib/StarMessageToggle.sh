#!/bin/sh
# Set starred flag on message.

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_STORE=$SMOKEPARROT_PATH/messages/

MESSAGE_NAME=$1
MESSAGE=$MESSAGE_STORE$MESSAGE_NAME

# Check that the message exists.
if [ ! -f $MESSAGE ]
then
	echo "The message does not exist."
else
  # Change the sharing state.
	if [ $(/bin/sed -n '9q8p' "$MESSAGE") == "STARRED" ]
	then
		/bin/sed -i '8s/STARRED/NOSTAR/' "$MESSAGE"
	else
		/bin/sed -i '8s/NOSTAR/STARRED/' "$MESSAGE"
	fi
fi