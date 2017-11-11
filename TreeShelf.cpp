//
// Created by Kuba on 06.11.2017.
//

#include "TreeShelf.h"


TreeShelf::Node::Node(TreeShelf::Node* parent, Cuboid* cuboid, double length, double depth, double xOffset, double yOffset, double zOffset) {
    parent_ = parent;
    cuboid_ = cuboid;
    length_ = length;
    depth_ = depth;
    xOffset_ = xOffset;
    yOffset_ = yOffset;
    zOffset_ = zOffset;
    left_ = nullptr;
    right_ = nullptr;
}

TreeShelf::Node::~Node() {
        delete left_;
        delete right_;
}

bool TreeShelf::Node::empty() const {
    return cuboid_ == nullptr;
}

bool TreeShelf::Node::fits(Cuboid &cuboid) const {
    if(cuboid.getLength() <= length_ && cuboid.getDepth() <= depth_) {
        return true;
    }
    if(cuboid.getLength() <= depth_ && cuboid.getDepth() <= length_) {
        cuboid.rotateHorizontally();
        return true;
    }
    return false;
}

void TreeShelf::Node::put(Cuboid* cuboid) {
    cuboid_ = cuboid;
    cuboid->setDisplacement({xOffset_, yOffset_, zOffset_});
    if(length_ - cuboid->getLength() > 0) {
        left_ = new Node(this, nullptr, length_ - cuboid->getLength(), depth_, cuboid->getLength() + xOffset_,yOffset_, zOffset_);
    }
    if(depth_ - cuboid->getDepth() > 0) {
        right_ = new Node(this, nullptr, cuboid->getLength(), depth_ - cuboid->getDepth(), xOffset_, yOffset_, cuboid->getDepth());
    }
}


TreeShelf::TreeShelf(double length, double depth, double heightOffset) {
    root_ = new Node(nullptr, nullptr, length, depth, 0.0, heightOffset, 0.0);
    currentHeight_ = 0.0;
}

TreeShelf::~TreeShelf() {
        delete root_;
}

TreeShelf::Iterator TreeShelf::begin() {
    return TreeShelf::Iterator(*this, root_);
}

TreeShelf::Iterator TreeShelf::end() {
    return TreeShelf::Iterator(*this, nullptr);
}

bool TreeShelf::add(Cuboid* cuboid) {
    for(TreeShelf::Iterator it = begin(); it != end(); ++it) {
        if(it->empty()) {
            if(it->fits(*cuboid)) {
                it->put(cuboid);
                if(cuboid->getHeight() > currentHeight_) {
                    currentHeight_ = cuboid->getHeight();
                }
                return true;
            }
        }
    }
    return false;
}

double TreeShelf::getCurrentHeight_() const {
    return currentHeight_;
}

TreeShelf::TreeShelf(TreeShelf &&other)
        : root_(other.root_)
        , currentHeight_(other.currentHeight_)
{
    other.root_ = nullptr;
    other.currentHeight_ = 0;
}

TreeShelf::TreeShelf(const TreeShelf &other) {
    if(other.root_ == nullptr)
        root_ = nullptr;
    else
        copyTree(this->root_, other.root_);
}

void TreeShelf::copyTree(TreeShelf::Node *&thisNode, TreeShelf::Node *root) {
    if(root == nullptr) {
        thisNode = nullptr;
    }
    else {
        thisNode = new Node(root->parent_, root->cuboid_, root->length_,
                            root->depth_, root->xOffset_, root->yOffset_, root->zOffset_);
        copyTree(thisNode->left_, root->left_);
        copyTree(thisNode->right_, root->right_);
    }
}

TreeShelf::Iterator::Iterator(TreeShelf& parent, TreeShelf::Node *current)
        : parent_(parent)
        , current_(current)
{}

bool TreeShelf::Iterator::operator==(const TreeShelf::Iterator &other) {
    return (&parent_ == &other.parent_ && current_ == other.current_);
}

bool TreeShelf::Iterator::operator!=(const TreeShelf::Iterator &other) {
    return (&parent_ != &other.parent_ || current_ != other.current_);
}

TreeShelf::Iterator &TreeShelf::Iterator::operator++() {
    if(current_->left_ != nullptr) {
        current_ = current_->left_;
    }
    else if(current_->right_ != nullptr) {
        current_ = current_->right_;
    }
    else {
        while(current_->parent_ != nullptr) {
            if(current_->parent_->right_ == current_) {
                current_ = current_->parent_;
            }
            else {
                current_ = current_->right_;
                return *this;
            }
        }
        current_ = nullptr;
        return *this;
    }
    return *this;
}

TreeShelf::Iterator TreeShelf::Iterator::operator++(int) {
    TreeShelf::Iterator copy = *this;
    ++(*this);
    return copy;
}

TreeShelf::Node *TreeShelf::Iterator::operator->() {
    return current_;
}

TreeShelf::Node *TreeShelf::Iterator::operator*() {
    return current_;
}
