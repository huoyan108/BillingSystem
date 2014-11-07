count = 0
devInfoTable = {}
function comdev(o)
--	count = count or 1;
	devInfoTable[count+1] = {}
	devInfoTable[count+1].dev = o.dev
	devInfoTable[count+1].speed = o.speed
	devInfoTable[count+1].bits = o.bits
	devInfoTable[count+1].event = o.event
	devInfoTable[count+1].stop = o.stop
	count = count +1
	print(table.maxn(devInfoTable))
	print(o.dev)
	print(o.speed)
	print(o.bits)
	print(o.event)
	print(o.stop)
end

local inputfile = 'data.lua'
dofile(inputfile)

