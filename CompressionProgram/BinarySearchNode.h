#pragma once
#include <string>
namespace sca {
	class BinarySearchNode {
	private:
		int frequency;
		std::string content;
		BinarySearchNode* branches[2] = { nullptr, nullptr };
	public:
		BinarySearchNode(int frequency = 0, std::string content = "");
		~BinarySearchNode();
		bool operator < (const BinarySearchNode& a) const { return frequency < a.frequency; }
		bool operator > (const BinarySearchNode& a) const { return frequency > a.frequency; }
		void setBranch(BinarySearchNode* leaf, const bool& OI) { this->branches[OI] = leaf; }
		BinarySearchNode* getBranch(const bool& OI) { return this->branches[OI]; }
		int getFrequency() const { return frequency; }
		std::string getContent() { return content; };
		void setContent(const std::string& content) { this->content = content; };
	};
}

