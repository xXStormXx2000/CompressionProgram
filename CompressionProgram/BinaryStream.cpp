#include "BinaryStream.h"
namespace sca {
	BinaryStream::BinaryStream(std::string data, int size) {
		if (data.size() < size / 8)return;
		this->data = data;
		this->size = size;
	}
	void BinaryStream::operator << (bool bit) {
		if (size % 8 == 0) {
			data.push_back(bit);
		}
		else {
			char byte = data.back();
			byte |= bit << size % 8;
			data[data.size() - 1] = byte;
		}
		size++;
	}
	void BinaryStream::operator >> (bool& bit) {
		if (pos >= size) return;
		bit = (data[pos / 8] >> pos % 8) & 1;
		pos++;
	}
	void BinaryStream::setPos(int newPos) {
		if (newPos < 0 || newPos > size) return;
		pos = newPos;
	}
	void BinaryStream::setData(const std::string& data, const int& size) {
		this->data = data;
		this->size = size;
	}
	bool BinaryStream::popBack() {
		char byte = data.back();
		size--;
		bool bit = (byte >> size % 8) & 1;
		if (size % 8 == 0) {
			data.pop_back();
		}
		else {
			byte &= ~(1 << size % 8);
			data[data.size() - 1] = byte;
		}
		return bit;
	}
}
