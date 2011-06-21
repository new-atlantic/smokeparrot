#!/usr/bin/haserl
<% echo -en "content-type: text/html\r\n\r\n" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
    "http://www.w3.org/TR/html4/strict.dtd">
<% PREFIX="/smokeparrot" %>
<html>
<head>
<%in /smokeparrot/html/meta.html %>
<script type="text/javascript">
<%in /smokeparrot/html/script.js %>
</script>
</head>
<body>
<div class="container">
<%in /smokeparrot/html/header.html %>
<div id="main" class="span-15 prepend-1 colborder">
<%in /smokeparrot/html/post-form.html %>
<div id="feed">
<h2>Recently Smoked</h2>
<%in /smokeparrot/html/filter.html %>
<hr class="space">
<%in /smokeparrot/html/messages.html %>
</div><!-- #feed -->
</div><!-- #main -->
<%in /smokeparrot/html/aside.html %>
<%in /smokeparrot/html/footer.html %>
</div><!-- .container -->
</body>
</html>

