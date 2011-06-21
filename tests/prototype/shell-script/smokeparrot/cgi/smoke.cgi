#!/usr/bin/haserl
<% POSTER=$(cat /smokeparrot/settings | awk 'BEGIN { FS = ":" } /USER/ { print $2}') %>
<% /smokeparrot/lib/CreateMessage.sh "$POST_message_body" "$POSTER" %>
<% echo -en "content-type: text/html\r\n\r\n" %>
<html>
<head>
<title>Post</title>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8">
<meta http-equiv="refresh" content="0; url=/cgi-bin/smokeparrot.cgi">
</head>
<body>
</body>
</html>

