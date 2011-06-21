#!/usr/bin/haserl
content-type: text/html

<% POSTER=$(cat /smokeparrot/settings | awk 'BEGIN { FS = ":" } /USER/ { print $2}') %>
<% /smokeparrot/lib/CreateMessage.sh "$POST_message_body" "$POSTER" %>
<html>
<head>
  <title>Post</title>
    <meta HTTP-EQUIV="REFRESH" content="0; url=/cgi-bin/smokeparrot.cgi">
  </head>
<body>
</body>
</html>
