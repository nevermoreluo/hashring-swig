//
// Created by never on 2021/12/25.
//

#ifndef HASHRING_HASHRING_H
#define HASHRING_HASHRING_H

#include <string>
#include <vector>
#include "hash/md5.h"
#include "consistent_hash_map.hpp"

struct vnode_t {
    vnode_t(std::size_t n,std::size_t v):node_id(n),vnode_id(v) {}

    std::string to_str() const {
        return std::string(std::to_string(node_id) + "%" + std::to_string(vnode_id));
    }

    std::size_t node_id; //主机ID,主机在主机列表中的索引
    std::size_t vnode_id; //虚拟节点ID

};

struct md5_hasher {
    std::string operator()(const vnode_t& node) {
        return md5(node.to_str());
    }

    typedef std::string result_type;
};

using consistent_hash_t = consistent_hash_map<vnode_t,md5_hasher>;
using node_id_t = int;

class HashRing {
public:

    void setVirtualNodeCount(int count);
    int getVirtualNodeCount();

    void insertNode(node_id_t nodeId);

    void removeNode(node_id_t nodeId);

    int findNode(std::string& key);

    int findNode(const std::string& key) { return findNode(const_cast<std::string&>(key)); }

    void resetAllNodes(std::vector<node_id_t>& nodeId);

    std::size_t size() const {
        return consistent_hash_.size();
    }

    bool empty() const {
        return consistent_hash_.empty();
    }

private:
    consistent_hash_t consistent_hash_;
    int virtualNodeCount = 100;
};


#endif //HASHRING_HASHRING_H
