#!/usr/bin/haserl
<%# The cgi-script that makes up the Smokeparrot WebUI %>
<%# %>
<%# Posting messages is done using this same script. %>
<%# Only invoke the message creation script if the POST-form has been used. %>
<% if [ "$POST_message_body" ]; then %>
  <% POSTER=$(cat /smokeparrot/settings | awk 'BEGIN { FS = ":" } /USER/ { print $2}') %>
  <% /smokeparrot/lib/CreateMessage.sh "$POST_message_body" "$POSTER" %>
<% fi %>
<% PREFIX="/smokeparrot" %>
<% echo -en "content-type: text/html\r\n\r\n" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
    "http://www.w3.org/TR/html4/strict.dtd">
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8">
    <title>Smokeparrot</title>
    <base href="/">
    <link rel="stylesheet" href="/css/blueprint/screen.css">
    <!--[if lt IE 8]><link rel="stylesheet" href="blueprint/ie" /><![endif]-->
    <link rel="stylesheet" href="/css/custom.css">
    <script type="text/javascript" src="js/jquery-1.6.min.js"></script>
    <script type="text/javascript">
    $(document).ready(function() {
      $("#post-text").keyup(function() {
        if ($(this).val() != "") {
          $("#post-button").removeAttr("disabled");
        } else {
          $("#post-button").attr("disabled", "disabled");
        }        
      });
      $(".debug").hide();
      $("#filter-button").click(function() {
        if ($("#filter-text").val() != "") {
          // Hide all messages
          $(".message").fadeOut();
          // Redisplay messages that contain filter text
          $(".message:contains(" + $("#filter-text").val() + ")").fadeIn();
        } else {
          // Show all messages
          $(".message").fadeIn();
        }
        
        return false;
      });
    });
    </script>
  </head>
  <body>
    <div class="container">
      <div id="header" class="span-22 prepend-1 append-1 last">
	<h1>Smokeparrot</h1>
      </div><!-- #header -->
      <div id="main" class="span-15 prepend-1 colborder">
	<div id="poster">
	  <form action="/cgi-bin/smokeparrot.cgi" method=POST>
	    <div id="post-form">
	      <textarea name="message_body" id="post-text" placeholder="Insert your post here"></textarea>
	      <%# The post button is disabled while the textarea is empty. %>
	      <button type=submit id="post-button" disabled="disabled">Post</button>
	    </div><!-- #post-form -->
	  </form>
	</div><!-- #poster -->
	<div id="feed">
	  <h2>Recently Smoked</h2>
	  <%# A filter to search messages. Currently functionality is implemented with jQuery in ./script.js %>
	  <div id="filter">
	    <input id="filter-text" type="text" class="text" placeholder="Insert your filter query here">
	    <button id="filter-button">Filter</button>
	  </div><!-- #filter -->
	  <hr class="space">
	  <div id="messages">
	    <% MESSAGE_STORE="$PREFIX/messages/" %>
	    <% MESSAGE_LIST=$(ls -l $MESSAGE_STORE | awk '{ print $9 }' | sort -r) %>
	    <% for MESSAGE_NAME in $MESSAGE_LIST; do %>
	    <%# Use different class for own messages. %>
	    <% if [ $(/bin/sed -n '5p' "$MESSAGE_STORE$MESSAGE_NAME") == "OWN" ]; %>
	    <% then %>
            <div class="own message">
	      <% else %>
              <div class="message">
		<% fi %>
		<div class="message-info">
		  <%# Use different symbols depending on sender, and distance to sender. %>
		  <% if [ $(/bin/sed -n '5p' "$MESSAGE_STORE$MESSAGE_NAME") == "OWN" ]; %>
		  <% then %>
		  <img alt="Symbol for times resmoked." src="img/loop_arrow_cool.png" class="message-icon" title="Resmoked 0 times"> 0
		  &nbsp;&nbsp;
		  <img alt="Sent from this node." src="img/circles_source.png" class="message-icon" title="This is your node">
		  <% else %>
		  <img alt="Symbol for times resmoked." src="img/loop_arrow_cool.png" class="message-icon" title="Resmoked <% /bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME" %> times"> <% echo -n $(/bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME") %>
		  &nbsp;&nbsp;
		  <% case $(/bin/sed -n '6p' "$MESSAGE_STORE$MESSAGE_NAME") in %>
		  <% [1-3]) echo '<img alt="Close distance to original sender." src="img/circles_close.png" class="message-icon" title="Node is at close distance">' ;; %>
		  <% [4-8]) echo '<img alt="Medium distance to original sender." src="img/circles_medium.png" class="message-icon" title="Node is at medium distance">'  ;; %>
		  <% *) echo '<img alt="Greater distance to original sender." src="img/circles_far.png" class="message-icon" title="Node is further away">' ;; %>
		  <% esac %>
		  <br>
		  <% fi %>
		</div><!-- .message-info -->
		<p class="debug"><% echo -n $MESSAGE_NAME %></p>
		<p class="sender-name quiet"><% echo -n $(/bin/sed -n '10p' "$MESSAGE_STORE$MESSAGE_NAME") %></p>
		<p class="timestamp quiet">Originally sent on: <% date -D %s -d $(/bin/sed -n '2p' "$MESSAGE_STORE$MESSAGE_NAME") %></p>
		<hr>
		<p class="content"><% echo -n $(/bin/sed -n '12,$p' "$MESSAGE_STORE$MESSAGE_NAME" | awk '{ print $0 "<br>"}') %></p>
	      </div><!-- .message -->
	      <% done %>           
	    </div><!-- #messages -->
	  </div><!-- #feed -->
	</div><!-- #main -->
	<div id="aside" class="span-6 append-1 last">
	  <%# This should display information about the local node and its neighbours. %>
	  <% POSTER=$(cat /smokeparrot/settings | awk 'BEGIN { FS = ":" } /USER/ { print $2}') %>
	  <% if [ ! $POSTER == "" ];then %>
	  <p><span class="quiet"><% echo -n $POSTER %>'s Node:</span><br><% echo -n $($PREFIX/lib/GetAddress.sh) %></p>
	  <% else %>
	  <p><span class="quiet">Own Node:</span><br><% echo -n $($PREFIX/lib/GetAddress.sh) %></p>
	  <% fi %>
	  <p><span class="quiet">Closest Nodes:</span><br>SecondNode</p>
	  <p><a href="http://naapurisopu.fi/smokeparrot">About Us</a></p>
	  <p><a href="#">Help</a></p>
	</div><!-- #aside -->
	<div id="footer" class="quiet span-22 prepend-1 append-1 last">
	  <hr>
	  <em>No parrots have been harmed in the production of this prototype.</em>
	</div><!-- #footer -->
      </div><!-- .container -->
  </body>
</html>
