--[[
Smokeparrot-LuCI - LuCI based interface for Smokeparrot

Copyright 2011 Torsti Schulz <torsti.schulz@iki.fi>

This file is part of the Smokeparrot.

Smokeparrot is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Smokeparrot is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
]]--

module("luci.controller.smokeparrot", package.seeall)

function index()
   entry({"apps", "smokeparrot"}, alias("apps", "smokeparrot", "stream"), "Smokeparrot", 90).dependent=false
   entry({"apps", "smokeparrot", "stream"}, call("display_messages"), "Stream", 10).dependent=false
   entry({"apps", "smokeparrot", "neighbours"}, template("smokeparrot/neighbours"), "Neighbours", 20).dependent=false
   entry({"apps", "smokeparrot", "config"}, template("smokeparrot/config"), "Settings", 30).dependent=false
   entry({"apps", "smokeparrot", "help"}, template("smokeparrot/help"), "Help", 40).dependent=false

   node("apps", "smokeparrot", "stream", "post").target = call("post_message")
end

function post_message()
   local value = luci.http.formvalue("sp_message-body") or luci.http.formvalue("sp_star-message") or luci.http.formvalue("sp_share-message") or luci.http.formvalue("sp_hide-message")

   if luci.http.formvalue("sp_message-body") then
      do_nothing = nil
   elseif luci.http.formvalue("sp_star-message") then
      do_nothing = nil
   elseif luci.http.formvalue("sp_share-message") then
      do_nothing = nil
   elseif luci.http.formvalue("sp_hide-message") then
      do_nothing = nil
   end

   luci.http.redirect(luci.dispatcher.build_url("apps", "smokeparrot"))
end

function display_messages()
   local dummy_message = {
      id = "message_id",
      name = "message_sender_name",
      node = "originating_node",
      text = "message_text",
      time = "1",
      starred = false,
      own = false,
      shared = true,
      visible = true,
   }

   local messages = { dummy_message, }

   table.sort(messages, function (a,b) return (a.time > b.time) end)

   luci.template.render("smokeparrot/stream", { messages = messages })
end
