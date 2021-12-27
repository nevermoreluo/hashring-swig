
package.cpath = package.cpath..";/home/never/github/hashring/cmake-build-debug/lua/?.so";

require("Hashring");


local f = Hashring.HashRing();


f:insertNode(5);
f:insertNode(9);
f:insertNode(3);
print(f:getVirtualNodeCount())
print(f:findNode("ssdsadadasadassadsadasdasdasdaaaaasdasda"))

print("-----")

print(f:findNode("asdadadasfsssssssssssssssssdddssafsdfsd"))



