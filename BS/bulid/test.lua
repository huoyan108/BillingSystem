devs = {}
dev  = "/dev/ttyr01"
devs[1] = dev
devs[2] = dev

count = table.maxn(devs)

for i=1,#devs do
print(devs[i])
end

print(table.maxn(devs))



