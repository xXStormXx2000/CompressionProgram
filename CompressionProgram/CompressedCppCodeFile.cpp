#include "CompressedCppCodeFile.h"
namespace sca {
    CompressedCppCodeFile::CompressedCppCodeFile(const std::vector<std::string>& codeFiles, const std::string& fileName) {
        for (auto& i : codeFiles)if (i.substr(i.find_last_of('.')) != ".cpp" && i.substr(i.find_last_of('.')) != ".h") throw;
        std::map<std::string, std::vector<std::string>> elements = generateElements(codeFiles);
        std::set<BinarySearchNode*, Compare> nodes = generateBinarySearchNodes(elements);
        this->tree = new BinarySearchTree(nodes);
        this->file = fileName + ".ccc";
        std::fstream thisFile(this->file, std::fstream::out | std::fstream::binary);
        int sizeOfTree = 0;
        for (auto i : this->tree->bitMap) { sizeOfTree += i.first.size() + i.second.getData().size() + 2; }
        for (int i = 0; i < sizeof(int); i++) {
            char c = sizeOfTree & 255;
            thisFile.write(reinterpret_cast<char*>(&c), 1);
            sizeOfTree = sizeOfTree >> 8;
        }
        for (auto i : this->tree->bitMap) {
            char cSize1 = i.first.size(), cSize2 = i.second.getSize();
            thisFile.write(reinterpret_cast<char*>(&cSize1), 1);
            for (char j : i.first) thisFile.write(reinterpret_cast<char*>(&j), 1);
            thisFile.write(reinterpret_cast<char*>(&cSize2), 1);
            for (char j : i.second.getData()) thisFile.write(reinterpret_cast<char*>(&j), 1);
        }
        for (auto codeFile : codeFiles) {
            BinaryStream bits = generateBinary(codeFile, elements);
            std::string fileName = codeFile.substr(codeFile.find_last_of('/\\') + 1);
            char c = fileName.size();
            thisFile.write(reinterpret_cast<char*>(&c), 1);
            thisFile << fileName;
            for (int i = 0; i < sizeof(int); i++) {
                c = (bits.getSize() >> 8 * i) & 255;
                thisFile.write(reinterpret_cast<char*>(&c), 1);
            }
            for (char i : bits.getData()) thisFile.write(reinterpret_cast<char*>(&i), 1);
        }
        thisFile.close();
    }
    CompressedCppCodeFile::CompressedCppCodeFile(const std::string& cccFileName) {
        if (cccFileName.substr(this->file.find_last_of('.')) != ".ccc") throw;
        this->file = cccFileName;
        unsigned char c;
        int size = 0, sizeOfTree = 0;
        std::string str, treeKey, treeElement;
        std::map<std::string, std::string> treeMap;
        std::ifstream cccFile(this->file, std::ifstream::in | std::ifstream::binary);
        for (int i = 0; i < sizeof(int); i++) {
            cccFile.read(reinterpret_cast<char*>(&c), 1);
            sizeOfTree += (c << (8 * i));
        }
        while (cccFile.read(reinterpret_cast<char*>(&c), 1)) {
            sizeOfTree--;
            treeElement = "";
            treeKey = "";
            str = "";
            size = c;
            for (int i = 0; i < size; i++) {
                cccFile.read(reinterpret_cast<char*>(&c), 1);
                sizeOfTree--;
                treeElement.push_back(c);
            }
            cccFile.read(reinterpret_cast<char*>(&c), 1);
            sizeOfTree--;
            size = c;
            for (int i = 0; i < size / 8 + (size % 8 != 0); i++) {
                cccFile.read(reinterpret_cast<char*>(&c), 1);
                sizeOfTree--;
                str.push_back(c);
            }
            BinaryStream bs(str, size);
            bool bit;
            while (bs.getPos() < bs.getSize()) {
                bs >> bit;
                treeKey += bit + '0';
            }
            treeMap[treeKey] = treeElement;
            if (sizeOfTree <= 1) break;
        }
        cccFile.close();
        this->tree = new BinarySearchTree(treeMap);
    }
    void CompressedCppCodeFile::decompress(std::string fileLocation) {
        if (fileLocation.back() != '\\' && fileLocation.back() != '/') fileLocation += '\\';
        std::string fileName, str;
        unsigned char c;
        int sizeOfTree = 0;
        std::ifstream cccFile(this->file, std::ifstream::in | std::ifstream::binary);
        for (int i = 0; i < sizeof(int); i++) {
            cccFile.read(reinterpret_cast<char*>(&c), 1);
            sizeOfTree += (c << (8 * i));
        }
        for (int i = 0; i < sizeOfTree; i++) cccFile.read(reinterpret_cast<char*>(&c), 1);
        while (cccFile.read(reinterpret_cast<char*>(&c), 1)) {
            str = "";
            fileName = fileLocation;
            unsigned int fSize = c;
            for (int i = 0; i < fSize; i++) {
                cccFile.read(reinterpret_cast<char*>(&c), 1);
                fileName += c;
            }
            unsigned int bitAmount = 0;
            for (int i = 0; i < sizeof(int); i++) {
                cccFile.read(reinterpret_cast<char*>(&c), 1);
                bitAmount += (c << (8 * i));
            }
            for (int i = 0; i < bitAmount / 8 + (bitAmount % 8 != 0); i++) {
                cccFile.read(reinterpret_cast<char*>(&c), 1);
                str += c;
            }
            std::fstream fileOut(fileName, std::fstream::out);
            BinaryStream bits(str, bitAmount);
            while (bits.getPos() < bits.getSize()) {
                std::string element = tree->getElementFromBinery(bits);
                fileOut << element;
            }
            fileOut.close();
        }
        cccFile.close();
    }
    CompressedCppCodeFile::~CompressedCppCodeFile() {
        delete tree;
    }
    void CompressedCppCodeFile::showTree() {
        this->tree->showTree();
    }
    std::set<BinarySearchNode*, Compare> CompressedCppCodeFile::generateBinarySearchNodes(const std::map<std::string, std::vector<std::string>>& elements) {
        std::set<BinarySearchNode*, Compare> nodes;
        std::map<std::string, int> frequencyMap;
        for (auto file : elements) {
            for (auto i : file.second) {
                if (frequencyMap.find(i) == frequencyMap.end()) frequencyMap[i] = 0;
                frequencyMap[i]++;
            }
        }
        for (auto i : frequencyMap) {
            BinarySearchNode* node = new BinarySearchNode(i.second, i.first);
            nodes.insert(node);
        }
        return nodes;
    }
    BinaryStream CompressedCppCodeFile::generateBinary(const std::string& cFile, std::map<std::string, std::vector<std::string>> elements) {
        BinaryStream bits, bs;
        bool bit;
        for (auto i : elements[cFile]) {
            bs = this->tree->getContentBits(i);
            while (bs.getPos() < bs.getSize()) {
                bs >> bit;
                bits << bit;
            }
        }
        return bits;
    }
    std::map<std::string, std::vector<std::string>> CompressedCppCodeFile::generateElements(const std::vector<std::string>& files) {
        std::map<std::string, std::vector<std::string>> elements;
        for (auto file : files) {
            char c, cPre = ' ';
            bool text = false;
            int textMode = 0;
            std::string str, escapedStr = "";
            std::ifstream fs(file, std::fstream::in);
            std::vector<std::pair<char, char>> wordCharacters = { {'0','9'},{'a','z'},{'A','Z'},{'_','_'} }, whiteSpaceCharacters = { {'\t', '\r'} };
            std::vector<char> pairCharacters = { ':', '=', '&', '|', '+', '-', '<', '>' };
            while (fs.get(c)) {
                bool word = false;
                for (auto charRange : wordCharacters) {
                    if (charRange.first <= c && c <= charRange.second) {
                        str.push_back(c);
                        word = true;
                        break;
                    }
                    if (word)break;
                }
                bool pair = false;
                for (auto i : pairCharacters) {
                    if (c == i) {
                        if (cPre == i) elements[file].push_back({ i,i });
                        pair = true;
                        break;
                    }
                    if (cPre == i && elements[file].back() != std::string({ i,i })) elements[file].push_back({ i });
                }
                if (word) { cPre = c; continue; }
                if (str != "")elements[file].push_back(str);
                str = "";
                if (pair) { cPre = c; continue; }
                elements[file].push_back({ c });
                cPre = c;

            }
            fs.close();
        }
        return elements;
    }
}
