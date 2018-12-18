io.write("Calling hey() ... \n")
local value = hey("First", "Second", 112233)
io.write(string.format("hey() returned: %s\n", tostring(value)))