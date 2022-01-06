

local function getCPath(buildPath, sep)
    sep=sep or'/'
    buildPath = buildPath or "lib"
    local fileName = debug.getinfo(1, "S").source:sub(2);
    fileName = fileName:match("(.*"..sep..")")
    return table.concat({fileName, "..", "..", buildPath, "lua", "?.so" }, sep)
end

package.cpath = package.cpath..";"..getCPath();

require("Hashring");


local f = Hashring.HashRing();


f:insertNode(5);
f:insertNode(9);
f:insertNode(3);
print(f:getVirtualNodeCount())
print(f:findNode("ssdsadadasadassadsadasdasdasdaaaaasdasda"))

print("-----")

print(f:findNode("asdadadasfsssssssssssssssssdddssafsdfsd"))



