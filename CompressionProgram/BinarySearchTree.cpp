#include "BinarySearchTree.h"
namespace sca {
	BinarySearchTree::BinarySearchTree(std::set<BinarySearchNode*, Compare>& data) {
		while (data.size() > 1) {
			BinarySearchNode* small = *data.begin();
			data.erase(data.begin());
			BinarySearchNode* big = *data.begin();
			data.erase(data.begin());
			BinarySearchNode* newNode = new BinarySearchNode(small->getFrequency() + big->getFrequency(), "");
			newNode->setBranch(small, 0);
			newNode->setBranch(big, 1);
			data.insert(newNode);
			if (data.size() == 1) this->root = newNode;

		}
		generateBitmap();
	};
	BinarySearchTree::~BinarySearchTree() {
		delete this->root;
	}
	BinaryStream BinarySearchTree::getContentBits(std::string content) {
		if (this->bitMap.find(content) != this->bitMap.end()) return this->bitMap[content];
		return {};
	}
	BinarySearchTree::BinarySearchTree(std::map<std::string, std::string> treeMap) {
		this->root = new BinarySearchNode;
		generateTreeFromMap(treeMap, "", this->root);
	}
	BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : bitMap(other.bitMap) {
		this->root = new BinarySearchNode(*(other.root));
	}
	BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
		bitMap = other.bitMap;
		this->root = new BinarySearchNode(*(other.root));
		return *this;
	}
	void BinarySearchTree::generateTreeFromMap(std::map<std::string, std::string>& lookUpMap, std::string bit, BinarySearchNode* trunk) {
		if (lookUpMap.find(bit) != lookUpMap.end()) {
			trunk->setContent(lookUpMap[bit]);
			return;
		}
		BinarySearchNode* node0, * node1;
		node0 = new BinarySearchNode();
		node1 = new BinarySearchNode();
		trunk->setBranch(node0, 0);
		trunk->setBranch(node1, 1);
		generateTreeFromMap(lookUpMap, bit + "0", node0);
		generateTreeFromMap(lookUpMap, bit + "1", node1);
	}
	void BinarySearchTree::showTree(BinarySearchNode* node, std::string bin) {
		if (node == nullptr)node = this->root;
		if (node->getContent() != "") {
			std::cout << bin << ": " << node->getContent() << '\n';
		}
		if (node->getBranch(0) != nullptr)showTree(node->getBranch(0), bin + "0");
		if (node->getBranch(1) != nullptr)showTree(node->getBranch(1), bin + "1");
	}
	std::string BinarySearchTree::getElementFromBinery(BinaryStream& bs) {
		BinarySearchNode* node = this->root;
		bool bit;
		while (true) {
			bs >> bit;
			node = node->getBranch(bit);
			if (node->getContent() != "") {
				return node->getContent();
			}
		}
		return {};
	}
	void BinarySearchTree::generateBitmap(BinarySearchNode* node, BinaryStream bin) {
		if (node == nullptr)node = this->root;
		if (node->getContent() != "") {
			bool a;
			while (bin.getPos() < bin.getSize()) {
				bin >> a;
			}
			bin.setPos(0);
			bitMap[node->getContent()] = bin;
		}
		if (node->getBranch(0) != nullptr) {
			bin << 0;
			generateBitmap(node->getBranch(0), bin);
			bin.popBack();
		}
		if (node->getBranch(1) != nullptr) {
			bin << 1;
			generateBitmap(node->getBranch(1), bin);
			bin.popBack();
		}
	}
}