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
      <div id="poster">
        <form action="/cgi-bin/smoke.cgi" method=POST>
          <textarea name="message_body" id="post-text" placeholder="Insert your post here"></textarea>
          <button type=submit id="post-button" disabled="disabled">Post</button>
        </form>
      </div>
      <div id="feed">
        <h2>Recently Smoked</h2>
        <div id="filter">
          <input id="filter-text" type="search" class="text" placeholder="Insert your filter query here">
          <button id="filter-button">Filter</button>
        </div>
        <hr class="space" />
        <div id="messages">
        <% MESSAGE_STORE="$PREFIX/messages/" %>
        <% MESSAGE_LIST=$(ls -l $MESSAGE_STORE | awk '{ print $9 }' | sort -r) %>
        <% for MESSAGE_NAME in $MESSAGE_LIST; do %>
          <% if [ $(/bin/sed -n '5p' "$MESSAGE_STORE$MESSAGE_NAME") == "OWN" ]; %>
          <% then %>
          <div class="own message">
          <% else %>
          <div class="message">
          <% fi %>
            <div class="message-info">
              <% if [ $(/bin/sed -n '5p' "$MESSAGE_STORE$MESSAGE_NAME") == "OWN" ]; %>
              <% then %>
              <img src="img/loop_arrow_cool.png" class="message-icon" title="Resmoked 0 times" /> 0
              &nbsp;&nbsp;
              <img src="img/circles_source.png" class="message-icon" title="This is your node" />
              <% else %>
              <img src="img/loop_arrow_cool.png" class="message-icon" title="Resmoked <% /bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME" %> times" /> <% /bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME" %>
              &nbsp;&nbsp;
              <% case $(/bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME") in %>
                <% [1-3]) echo '<img src="img/circles_close.png" class="message-icon" title="Node is at close distance" />' ;; %>
                <% [4-8]) echo '<img src="img/circles_medium.png" class="message-icon" title="Node is at medium distance" />'  ;; %>
                <% *) echo '<img src="img/circles_far.png" class="message-icon" title="Node is further away" />' ;; %>
              <% esac %>
              <br>
              <% fi %>
            </div><!-- .message-info -->
            <p class="debug"><% echo $MESSAGE_NAME %></p>
            <p class="sender-name quiet"><% /bin/sed -n '10p' "$MESSAGE_STORE$MESSAGE_NAME" %></p>
            <p class="timestamp quiet"><% /bin/sed -n '2p' "$MESSAGE_STORE$MESSAGE_NAME" %></p>
            <hr />
            <p class="content"><% /bin/sed -n '12,$p' "$MESSAGE_STORE$MESSAGE_NAME" | awk '{ print $0 "<br>"}' %></p>
          </div><!-- .message -->
        <% done %>           
        </div>
      </div>
    </div><!-- #main -->
    <%in /smokeparrot/html/aside.html %>
    <%in /smokeparrot/html/footer.html %>
  </div>
</body>
</html>
