module("luci.controller.myapp.mymodule", package.seeall)

function index()
   entry({"smokeparrot"}, template("smokeparrot"), "Smokeparrot", 20).dependent=false

end