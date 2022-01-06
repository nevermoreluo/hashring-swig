import sys
import os
build_path = "lib"
cpath = os.path.abspath(os.path.dirname(__file__))+"/../../"+build_path+"/python";
sys.path.append(cpath);

import Hashring

f = Hashring.HashRing();

f.insertNode(5);
f.insertNode(9);
f.insertNode(3);
print(f.getVirtualNodeCount())
print(f.findNode("ssdsadadasadassadsadasdasdasdaaaaasdasda"))

print("-----")

print(f.findNode("asdadadasfsssssssssssssssssdddssafsdfsd"))









