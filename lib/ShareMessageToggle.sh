#!/bin/sh
# Change the share status of a smokeparrot message.

source ./env.sh

MESSAGE_NAME=$1
MESSAGE="$MESSAGE_STORE$MESSAGE_NAME"

# Check that the message exists.
if [ ! -f $MESSAGE ]
then
	echo "The message does not exist."
else
  # Change the sharing state.
	if [ $(/bin/sed -n '5q4p' "$MESSAGE") == "SHARE" ]
	then
		/bin/sed -i '4s/SHARE/NOSHARE/' "$MESSAGE"
	else
		/bin/sed -i '4s/NOSHARE/SHARE/' "$MESSAGE"
	fi
fi
