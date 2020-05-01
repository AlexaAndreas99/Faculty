#include "BSTNode.h"





BSTNode::BSTNode()
{
	this->value.first = NULL;
	this->value.second = NULL;
	this->left = -1;
	this->right = -1;
}

BSTNode::BSTNode(Telem v, int l, int r)
{
	this->value = v;
	this->left = l;
	this->right = r;
}

Telem BSTNode::getValue() const {
	return value;
}

void BSTNode::setValue(Telem e) {
	this->value = value;
}

int BSTNode::getLeftSon() const {
	return left;
}

void BSTNode::setLeftSon(int leftSon) {
	this->left = leftSon;
}

int BSTNode::getRightSon() const {
	return right;
}

void BSTNode::setRightSon(int rightSon) {
	this->right = rightSon;
}

bool BSTNode::isNull() {
	return value.first == -1;
}

bool BSTNode::isLeaf() {
	return left == -1 && right == -1;
}

BSTNode::~BSTNode()
{
}
