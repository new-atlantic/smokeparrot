#!/bin/sh
# Transfers messages from other Smokeparrot nodes into the queue.

SMOKEPARROT_PATH=/home/smokeparrot
SHARE_QUEUE=$SMOKEPARROT_PATH/shared

MESSAGE_QUEUE=$SMOKEPARROT_PATH/queue/

USERNAME=smokeparrot
IDENTITY_FILE=$SMOKEPARROT_PATH/.ssh/id_rsa
REMOTE_HOST="$1"

# Transfer the messages from the remote hosts message store to the local queue.
/usr/bin/scp -S $SMOKEPARROT_PATH/lib/dbclient-noask.sh -i $IDENTITY_FILE -r $USERNAME@$REMOTE_HOST:$SHARE_QUEUE/* $MESSAGE_QUEUE 
