/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	Header file for class cache													*
*																							*
*File Name: cache.h																			*
*Date: 02/21/2016																			*
*********************************************************************************************/




#ifndef CACHE_H
#define CACHE_H
#include "set_blocks.h"

class cache
{
public:
	cache(int a, int b);
	void set_c_size(int c,int d);
	void cache_alloc();
	set_blocks read_cache(int e);
	void write_cache(int index, int block_num, int tag, bool LRU, bool valid,bool dirty);
	void wr_bl_lru(int ind, int blk_num, bool lru);
	
private:
	int c_size;
	int assoc;
	set_blocks *sets;
};

#endif // CACHE_H
