devs = {}
--dev  = "/dev/ttyr01"
--devs[1] = dev
--devs[2] = dev

--count = table.maxn(devs)

--for i=1,#devs do
--print(devs[i])
--end

--print(table.maxn(devs))

comdev = {dev="/dev/ttyr01",speed=115200,bits=8,event="N",stop=1}
devs[1] = comdev


count = table.maxn(devs)
print(count)


for i=1,#devs do
print(devs[i].dev)
print(devs[i].speed)
print(devs[i].bits)
print(devs[i].event)
print(devs[i].stop)
end

