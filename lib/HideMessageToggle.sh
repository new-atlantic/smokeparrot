#!/bin/sh
# Set hidden flag for a smokeparrot message.

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_STORE=$SMOKEPARROT_PATH/messages/
SHARE_QUEUE=$SMOKEPARROT_PATH/shared/

MESSAGE_NAME=$1
MESSAGE=$MESSAGE_STORE$MESSAGE_NAME

# Check that the message exists.
if [ ! -f $MESSAGE ]
then
	echo "The message does not exist."
else
	if [ $(/bin/sed -n '8q7p' "$MESSAGE") == "VISIBLE" ]
	then
	        /bin/sed -i '7s/VISIBLE/HIDDEN/' "$MESSAGE"
		/bin/sed -i '4s/SHARE/NOSHARE/' "$MESSAGE"
		/bin/rm "$SHARE_QUEUE$MESSAGE_NAME"
	else
	        /bin/sed -i '7s/HIDDEN/VISIBLE/' "$MESSAGE"
	fi
    # Hide and unshare message.
fi
