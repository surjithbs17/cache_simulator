/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	cpp file for class cache													*
*																							*
*File Name: cache.cpp																		*
*Date: 02/21/2016																			*
*********************************************************************************************/


#include "cache.h"
#include "set_blocks.h"
#include "block.h"
#include <iostream>
using namespace std;

cache::cache(int a, int b)
{
	set_c_size(a,b);
	
}

void cache::set_c_size(int c, int d)
{
	c_size = c;
	assoc = d;
}

void cache::cache_alloc()
{
	sets = (set_blocks *)malloc(c_size*sizeof(set_blocks));
	
	//sets->alloc_block(assoc);
	for (int i = 0; i < c_size; i++)
	{
		sets[i].alloc_block(assoc);
	}

}

set_blocks cache::read_cache(int e)
{
	return sets[e];
}

void cache::write_cache(int index, int block_num, int tag, bool LRU, bool valid,bool dirty)
{
	sets[index].write_block(block_num, tag, LRU, valid,dirty);
}

void cache::wr_bl_lru(int ind, int blk_num, bool lru)
{
	sets[ind].write_block_LRU(blk_num, lru);
}

