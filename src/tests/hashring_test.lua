
package.cpath = package.cpath..";/home/never/github/hashring/cmake-build-debug/lua/?.so";

require("Hashring");


local f = Hashring.HashRing();

print(f:getVirtualNodeCount())


