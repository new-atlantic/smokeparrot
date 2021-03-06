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

require "luasql.sqlite3"
local db_file = "/tmp/smokeparrot_test.sqlite3"

function index()
   entry({"apps", "smokeparrot"}, alias("apps", "smokeparrot", "stream"), "Smokeparrot", 90).dependent=false
   entry({"apps", "smokeparrot", "stream"}, call("display_messages"), "Stream", 10).dependent=false
   entry({"apps", "smokeparrot", "neighbours"}, template("smokeparrot/neighbours"), "Neighbours", 20).dependent=false
   entry({"apps", "smokeparrot", "config"}, template("smokeparrot/config"), "Settings", 30).dependent=false
   entry({"apps", "smokeparrot", "help"}, template("smokeparrot/help"), "Help", 40).dependent=false

   node("apps", "smokeparrot", "stream", "post").target = call("post_message")
   node("apps", "smokeparrot", "stream", "star").target = call("star_message")
   node("apps", "smokeparrot", "stream", "share").target = call("share_message")
   node("apps", "smokeparrot", "stream", "hide").target = call("hide_message")
end

function post_message()
   local message = luci.http.formvalue("sp_message-body")
   if message:gsub("^%s*", "") ~= "" then
      local env = assert (luasql.sqlite3())
      local conn = assert (env:connect(db_file))
      math.randomseed (os.time())
      local res = assert (conn:execute(string.format([[
	INSERT INTO messages VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')]],
                math.random(1, 100000), "", os.time(),
		string.gsub(message, "'", "''"), 0, 1, 1, 0 )))
      conn:close()
      env:close()
   end
   luci.http.redirect(luci.dispatcher.build_url("apps", "smokeparrot"))
end

local function update_message(action, column)
   local env = assert (luasql.sqlite3())
   local conn = assert (env:connect(db_file))
   local id = luci.http.formvalue("sp_" .. action .. "-message")
   local state = luci.http.formvalue("sp_" .. action .. "-state")

   if state == "0" then
      state = 1
   else
      state = 0
   end

   local res = assert (conn:execute(string.format([[
	UPDATE messages SET "%s" = '%s' WHERE "id" = '%s';]], column, state, id )))
   conn:close()
   env:close()

   luci.http.redirect(luci.dispatcher.build_url("apps", "smokeparrot"))
end

function star_message()
   update_message("star","starred")
end

function share_message()
   update_message("share","shared")
end

function hide_message()
   update_message("hide","hidden")
end

function sanitize_output(text)
    local replacements = {
        ['&' ] = '&amp;', 
        ['<' ] = '&lt;', 
        ['>' ] = '&gt;', 
        ['\n'] = '<br/>'
    }
    return text:gsub('[&<>\n]', replacements)
end

function display_messages()
   local env = assert (luasql.sqlite3())
   local conn = assert (env:connect(db_file))
   local cur = assert (conn:execute"SELECT id, name, time, text, own, starred, shared, hidden FROM messages")
   local row = cur:fetch ({}, "a")

   local messages = {}

   while row do
      table.insert (messages, {
		       id = row.id,
		       name = row.name,
		       time = row.time,
		       node = "",
		       text = sanitize_output(row.text),
		       starred = row.starred,
		       own = row.own,
		       shared = row.shared,
		       hidden = row.hidden})
      row = cur:fetch (row, "a")
   end

   cur:close()
   conn:close()
   env:close()

   table.sort(messages, function (a,b) return (a.time > b.time) end)
   luci.template.render("smokeparrot/stream", { messages = messages })
end
