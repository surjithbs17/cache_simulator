/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	cpp file for class set_blocks												*
*																							*
*File Name: set_blocks.cpp																	*
*Date: 02/21/2016																			*
*********************************************************************************************/



#include "set_blocks.h"
#include <iostream>
#include "block.h"
using namespace std;
set_blocks::set_blocks(int assoc)
{
	alloc_block(assoc);
	
	
}


void set_blocks::alloc_block(int y)
{
	size_b = y;
	blocks = (block *)malloc(size_b*sizeof(block));
	for (int i = 0; i < size_b; i++)
	{
		blocks[i].invalidate();
		blocks[i].make_not_dirty();
		blocks[i].set_tag(0);
		blocks[i].write_LRU(false);
	}
}

block set_blocks::read_block(int z)
{
	return blocks[z];
}

void set_blocks::write_block(int a, int tag, bool LRU ,bool valid,bool dirty )
{
	blocks[a].set_tag(tag);
	blocks[a].write_LRU(LRU);
	if (dirty)
	{
		blocks[a].make_dirty();
	}
	else
	{
		blocks[a].make_not_dirty();
	}

	if(valid)
	{
		blocks[a].validate();
	}
}

void set_blocks::write_block_LRU(int b, bool lru)
{
	blocks[b].write_LRU(lru);
}