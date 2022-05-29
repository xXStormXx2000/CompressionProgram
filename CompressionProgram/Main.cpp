#include <vector>
#include "CompressedCppCodeFile.h"
int main() {
    std::string fileName = "test", fileLocation = "";
    {
        std::vector <std::string> codeFilesNames = { "BinarySearchNode.h", "BinarySearchTree.h", "BinaryStream.h","CompressedCppCodeFile.h", "BinarySearchNode.cpp", "BinarySearchTree.cpp", "BinaryStream.cpp", "CompressedCppCodeFile.cpp", "Main.cpp" };
        sca::CompressedCppCodeFile test1(codeFilesNames, fileName);
    }
    sca::CompressedCppCodeFile test2(fileName + ".ccc");
    test2.decompress(fileLocation);
    return 0;
}
