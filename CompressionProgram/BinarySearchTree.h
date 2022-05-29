#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "BinarySearchNode.h"
#include "BinaryStream.h"
#include <map>
#include <set>
#include "Compare.h"

namespace sca {
	class BinarySearchTree {
	private:
		BinarySearchNode* root;

		void generateTreeFromMap(std::map<std::string, std::string>&, std::string, BinarySearchNode*);
		void generateBitmap(BinarySearchNode* = nullptr, BinaryStream = {});
	public:
		std::map<std::string, BinaryStream> bitMap;
		BinarySearchTree(std::set<BinarySearchNode*, Compare>&);
		BinarySearchTree(std::map<std::string, std::string>);
		~BinarySearchTree();
		BinaryStream getContentBits(std::string);
		BinarySearchNode* getRoot() { return this->root; };
		void showTree(BinarySearchNode* = nullptr, std::string = "");
		std::string getElementFromBinery(BinaryStream&);
	};
}

