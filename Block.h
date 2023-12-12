#pragma once
#include <string>

class Block {
private:
	std::string fileName;

public:
	enum Type {
		none = -1,
		dirt = 0,
	};

	Type type;

	Block();
	void setFileName(std::string);

};