//
// Created by Kuba on 06.11.2017.
//

#ifndef AAL_TREE_SHELF_H
#define AAL_TREE_SHELF_H


#include "Cuboid.h"

class TreeShelf {
private:
    struct Node;

    Node* root_;
    double currentHeight_;

public:
    class Iterator;

    TreeShelf() = delete;
    TreeShelf(double length, double height, double heightOffset);
    TreeShelf(const TreeShelf& other);
    TreeShelf(TreeShelf&& other) noexcept;
    ~TreeShelf();
    Iterator begin();
    Iterator end();
    bool add(Cuboid* cuboid);
    void copyTree(Node*& thisNode, Node* root);
    double getCurrentHeight_() const;
};

class TreeShelf::Node {
public:
    Node* left_;
    Node* right_;
    Node* parent_;

    double length_;
    double depth_;

    double xOffset_;
    double yOffset_;
    double zOffset_;

    Cuboid* cuboid_;

    Node(Node* parent, Cuboid* cuboid, double length, double height, double xOffset, double yOffset, double zOffset);
    ~Node();
    bool empty() const;
    bool fits(Cuboid& cuboid) const;
    void put(Cuboid* cuboid);
};

class TreeShelf::Iterator {
private:
    TreeShelf& parent_;
    Node* current_;

public:
    Iterator(TreeShelf& parent, Node* current);
    Iterator(const Iterator& other) = default;
    ~Iterator() = default;
    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
    Iterator& operator++();
    Iterator operator++(int);
    TreeShelf::Node* operator->();
    TreeShelf::Node* operator*();

};

#endif //AAL_TreeShelf_H
