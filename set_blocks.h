/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	Header file for class set_blocks											*
*																							*
*File Name: set_blocks.h																	*
*Date: 02/21/2016																			*
*********************************************************************************************/


#ifndef SET_BLOCKS_H
#define SET_BLOCKS_H
#include "block.h"

class set_blocks
{
public:
	set_blocks(int assoc);
	void alloc_block(int y);
	block read_block(int z);
	void write_block(int a, int tag, bool LRU, bool valid,bool dirty);
	void write_block_LRU(int b, bool lru);
private:
	int size_b;
	block *blocks;
};

#endif // SET_BLOCKS_H
