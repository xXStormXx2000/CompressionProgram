#include "BinarySearchNode.h"
namespace sca {
	BinarySearchNode::BinarySearchNode(int frequency, std::string content) {
		this->frequency = frequency;
		this->content = content;
	}
	BinarySearchNode::~BinarySearchNode() {
		delete this->branches[0];
		delete this->branches[1];
	}
}