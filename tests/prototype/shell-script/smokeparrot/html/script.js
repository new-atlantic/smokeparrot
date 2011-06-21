    $(document).ready(function() {
      $("#post-text").keyup(function() {
        if ($(this).val() != "") {
          $("#post-button").removeAttr("disabled");
        } else {
          $("#post-button").attr("disabled", "disabled");
        }        
      });
      
      $(".debug").hide();
/*      $("#post-button").click(function() {
        var message = '\
          <div class="own message">\
            <div class="message-info">\
              <img src="img/loop_arrow_cool.png" class="message-icon" title="Resmoked 0 times" /> 0\
              &nbsp;&nbsp;\
              <img src="img/circles_source.png" class="message-icon" title="This is your node" />\
            </div>\
            <p class="sender-name quiet">OwnNode</p>\
            <hr />\
            <p class="content">' + $("#post-text").val() + '</p>\
          </div>';
        
        $(message)
          .prependTo($("#messages"))
          .hide()
          .fadeIn("slow");
        $("#post-text").val("");
        $("#post-button").attr("disabled", "disabled");
        return false;
      });*/
      
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

