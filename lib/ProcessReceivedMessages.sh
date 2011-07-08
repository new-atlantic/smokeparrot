#!/bin/sh
# Processes new received messages in the queue

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_STORE=$SMOKEPARROT_PATH/messages/

MESSAGE_LIST=$(ls -l $MESSAGE_STORE | awk '{ print $9 }' | sort -r)
MESSAGE_QUEUE=$SMOKEPARROT_PATH/queue/
QUEUE_LIST=$(ls -l $MESSAGE_QUEUE | awk '{ print $9 }' | sort -r)

# TODO: Set up an option, to ignore messages older than the argument or a default in the SETTINGS-file.

for QUEUED_MESSAGE_NAME in $QUEUE_LIST; do
  IN_STORE=0
  for MESSAGE_NAME in $MESSAGE_LIST; do
    # If message hash of queued message matches hash of message in store, increment its counter and set distance traveled to the smaller of the two, after first incrementing the distance traveled of queued message by one.
    if [ $(/bin/sed -n '3p' "$MESSAGE_STORE$MESSAGE_NAME") == $(/bin/sed -n '3p' "$MESSAGE_QUEUE$QUEUED_MESSAGE_NAME") ]; then
      # Increment times received by one.
      /bin/sed -i "5s/$(cat $MESSAGE_STORE$MESSAGE_NAME |  awk '/RECEIVED/ { print $2}')/$(cat $MESSAGE_STORE$MESSAGE_NAME |  awk '/RECEIVED/ { print $2+1}')/" "$MESSAGE_STORE$MESSAGE_NAME"
      # Set to lower value of shortest distance traveled.
      DIST_IN_STORE=$(/bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME")
      DIST_IN_QUEUE=$(/bin/sed -n '6p' "$MESSAGE_QUEUE$QUEUED_MESSAGE_NAME")
      if [ $DIST_IN_STORE -gt $(expr $DIST_IN_QUEUE + 1)  ]; then
        /bin/sed -i "6s/$DIST_IN_STORE/$(expr $DIST_IN_QUEUE + 1)/" "$MESSAGE_STORE$MESSAGE_NAME"
      fi
      IN_STORE=1
    fi
  done
  # If message does not exist in store.
  if [ $IN_STORE == 0 ]; then
    TIMESTAMP=$(date +%s)
    MESSAGE_RECEIVED="$TIMESTAMP"
    HASH=$(/bin/sed -n '3p' "$MESSAGE_QUEUE$QUEUED_MESSAGE_NAME")
    NEW_NAME="$MESSAGE_RECEIVED-$HASH.txt"
    echo $NEW_NAME
    # Move message to the store and rename it with the current time.
    /bin/mv "$MESSAGE_QUEUE$QUEUED_MESSAGE_NAME" "$MESSAGE_STORE$NEW_NAME"
    DISTANCE=$(/bin/sed -n '6p' "$MESSAGE_STORE$NEW_NAME")
    # Increment distance traveled.
    /bin/sed -i "6s/$DISTANCE/$(expr $DISTANCE + 1)/" "$MESSAGE_STORE$NEW_NAME"
    # Set times received to 1.
    /bin/sed -i "5s/.*/RECEIVED 1/" "$MESSAGE_STORE$NEW_NAME"
  else
    /bin/rm "$MESSAGE_QUEUE$QUEUED_MESSAGE_NAME"
  fi
done

