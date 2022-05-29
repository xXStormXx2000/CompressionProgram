#pragma once
#include <string>
namespace sca {
	class BinaryStream {
	private:
		std::string data = "";
		int size = 0;
		int pos = 0;
	public:
		BinaryStream() {};
		BinaryStream(std::string, int);
		void operator << (bool);
		void operator >> (bool&);
		void setPos(int);
		void setData(const std::string&, const int&);
		bool popBack();
		int getSize() const { return size; }
		int getPos() const { return pos; }
		std::string getData() const { return data; }
	};
}

