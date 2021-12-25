//
// Created by never on 2021/12/25.
//

#include "hashring.h"

void HashRing::insertNode(node_id_t nodeId)
{
    for (int i = 0; i < virtualNodeCount; i++)
    {
        consistent_hash_.insert(vnode_t(nodeId, i));
    }
}

void HashRing::removeNode(node_id_t nodeId)
{
    for (int i = 0; i < virtualNodeCount; i++)
    {
        consistent_hash_.erase(vnode_t(nodeId, i));
    }
}

node_id_t HashRing::findNode(std::string& key)
{
    auto it = consistent_hash_.find(md5(key));
    if (it != consistent_hash_.end())
    {
        return it->second.node_id;
    }
    // never be here, unless node is empty
    return 0;
}

void HashRing::resetAllNodes(std::vector<node_id_t>& nodeIds)
{
    consistent_hash_.clear();
    for (node_id_t id: nodeIds)
    {
        insertNode(id);
    }
}

void HashRing::setVirtualNodeCount(int count)
{
    virtualNodeCount = count;
}

int HashRing::getVirtualNodeCount()
{
    return virtualNodeCount;
}