#!/bin/sh
# Gets the messages from all neighbours.

SMOKEPARROT_PATH=/home/smokeparrot
MESSAGE_STORE=$SMOKEPARROT_PATH/messages/

FUNCTIONS=$SMOKEPARROT_PATH/lib

NEIGHBOURS="$($FUNCTIONS/GetNeighbours.sh)"

for IP_ADDRESS in $NEIGHBOURS; do
  $FUNCTIONS/TransferMessages.sh "$IP_ADDRESS"
# DEBUG  ls $SMOKEPARROT_PATH/messages
# DEBUG  ls $SMOKEPARROT_PATH/queue
  $FUNCTIONS/KeepSharedMessages.sh
# DEBUG  ls $SMOKEPARROT_PATH/messages
# DEBUG  ls $SMOKEPARROT_PATH/queue
  $FUNCTIONS/ProcessReceivedMessages.sh
# DEBUG  ls $SMOKEPARROT_PATH/messages
# DEBUG  ls $SMOKEPARROT_PATH/queue
done
