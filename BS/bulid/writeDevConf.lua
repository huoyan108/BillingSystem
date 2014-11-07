function serialize(f,o)
	if type(o) == "number" then
		f:write(o)
	elseif type(o) == "string" then
		f:write(string.format("%q",o))
	elseif type(o) == "table" then
		f:write("{\n")
		for k,v in pairs(o) do
		f:write("",k,"=")
		serialize(f,v)
		f:write(",\n")
		end
		f:write("}\n")
	else
		print('error')
	end
end


filename = 'data.lua'
mode = 'w'
local f = assert(io.open(filename,mode))
data = {}
--f:write('comdev')
--serialize(f,{dev='\\ttyr01',speed=15200,bits=8,event='N',stop=1})
--serialize(f,data)
f:close()

function writeDevconfig()
    filename = 'data.lua'
    value = data
    mode = 'a'
    local f = assert(io.open(filename,mode))

    f:write('comdev')

    serialize(f,value)

    f:close()
end
