===============================
 Smokeparrot (testing version)
===============================

This is a test version of the proximity based microblogging application **Smokeparrot**. It is written mainly in *shell* and deployed as a cgi-script using haserl_.

.. _haserl: http://haserl.sourceforge.net/

Deployment
==========

This test version of **Smokeparrot** has been tested on the Linux-based wireless router firmware OpenWRT_. The test version of Smokeparrot is placed under the directory */smokeparrot/*, that is, outside the regular file system hierarchy used on OpenWRT. A symbolic link to */smokeparrot/cgi/smokeparrot.cgi* should be placed into /www/cgi-bin/.

.. _OpenWRT: http://www.openwrt.org/

Messages
========

The test version of **Smokeparrot** uses flat files to store messages, one file per message. Messages are stored in the folder */smokeparrot/messages/* and incoming messages from other **Smokeparrot**\-nodes are placed into */smokeparrot/queue/* to await processing.

Message structure
-----------------

The messages have a header that contains information about the message. The header ranges from line 1 to 10. The message body starts from line 12.

Message header lines:

 1. Address of sender. At the moment this is meant to be the MAC-address of the sending network device. Possibly to be replaced by the IP-address of the sender.
 2. Timestamp. Time the message was initially created. It is written in `unix time`_.
 3. The hash of the message. A checksum calculated using *md5* over the sender address, message creation time and the message body. While the *md5* algorithm is no longer considered *cryptographically safe* it is useful enough for its intended purpose in **Smokeparrot**.
 4. The fourth line contains a tag to indicate whether the message should be shared to other **Smokeparrot**\-nodes. The possible legal values are *SHARE* and *NOSHARE*. At the moment the implementation of this property is done on the receiving **Smokeparrot**\-node. See `Message transfer`_ and `Message processing`_.
 5. The fifth line contains a tag or tag-and-value indicating whether the message was created on the device it is stored on, or if it was received from another **Smokeparrot**\-node and how many times the same message was received already. The legal values are *OWN* and *RECEIVED X* where X is an integer. When a message is first received X is set to 1. When the same message is received again, it is recognized as a duplicate (by comparing hashes) and times-received (X) of the message that was received earlier is incremented by one.
 6. The sixth line is a single integer that represents the shortest path from the original sender to the current node. Its initial value is 0 and it is incremented by one on a receiving node. When the same message is received again. The value of the sixth line (+ 1) is compared to that of the same message in the message store. The value of the sixth line of the originally received message is then set to the smaller of the two values. This way the sixth line always represents the shortest known (message) path to the original sender.
 7. Lines 7 through 9 have not been defined yet, and are thus reserved for additions to the message header.
 
 10. The tenth line is reserved for a user-defined name for the message sender.
 11. Line eleven is empty to separate the message body from the header.
 12. The twelfth line and all subsequent lines contain the message body.


.. _`unix time`: http://unixtime.info/

Message naming
--------------

Messages have a two-part name. The first is a timestamp, in unix time format, that represent the time when the message was received, and  is separated by a hyphen from the message-hash. The ending is *.txt*.

Networking
==========

Message transfer
----------------

The test version of **Smokeparrot** will be using scp for message transfer. The receiver will copy the messages from the sender into its own queue. **TODO**

Message processing
------------------

**TODO**

Neighbour detection
-------------------

**TODO**
