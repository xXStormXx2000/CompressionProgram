#include "BinarySearchNode.h"
namespace sca {
	BinarySearchNode::BinarySearchNode(int frequency, std::string content)  {
		this->frequency = frequency;
		this->content = content;
	}
	BinarySearchNode::BinarySearchNode(const BinarySearchNode& other) 
		: frequency(other.frequency), content(other.content) {
		if (other.branches[0] != nullptr) {
			this->branches[0] = new BinarySearchNode(*(other.branches[0]));
		}
		if (other.branches[1] != nullptr) {
			this->branches[1] = new BinarySearchNode(*(other.branches[1]));
		}
	}
	BinarySearchNode& BinarySearchNode::operator=(const BinarySearchNode& other) {
		this->frequency = other.frequency;
		this->content = other.content;
		if (other.branches[0] != nullptr) {
			this->branches[0] = new BinarySearchNode(*(other.branches[0]));
		}
		if (other.branches[1] != nullptr) {
			this->branches[1] = new BinarySearchNode(*(other.branches[1]));
		}
		return *this;
	}
	BinarySearchNode::~BinarySearchNode() {
		if (this->branches[0] != nullptr) delete this->branches[0];
		if (this->branches[1] != nullptr) delete this->branches[1];
	}
}