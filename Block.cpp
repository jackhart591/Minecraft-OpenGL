#include "Block.h"

Block::Block()
{
	this->setFileName("none");
}

void Block::setFileName(std::string s)
{
	this->fileName = s;
}
