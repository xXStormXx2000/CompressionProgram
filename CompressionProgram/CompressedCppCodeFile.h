#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BinarySearchTree.h"
#include <map>
#include <set>
#include "Compare.h"
#include "BinaryStream.h"
namespace sca {
	class CompressedCppCodeFile {
	private:
		BinarySearchTree* tree;
		std::string file;

		std::set<BinarySearchNode*, Compare> generateBinarySearchNodes(const std::map<std::string, std::vector<std::string>>&);
		BinaryStream generateBinary(const std::string&, std::map<std::string, std::vector<std::string>>);
		std::map<std::string, std::vector<std::string>> generateElements(const std::vector<std::string>&);
	public:
		CompressedCppCodeFile(const std::vector<std::string>&, const std::string&);
		CompressedCppCodeFile(const std::string&);
		void decompress(std::string = "");
		~CompressedCppCodeFile();
		void showTree();
	};
}

