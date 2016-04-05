/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	header file for class block													*
*																							*
*File Name: block.h																			*
*Date: 02/21/2016																			*
*********************************************************************************************/



#ifndef BLOCK_H
#define BLOCK_H


class block
{
public:
	block();
	void validate();
	void invalidate();
	bool check_valid();
	void set_tag(int x);
	int read_tag();
	bool read_LRU();
	void write_LRU(bool d);
	bool check_dirty();
	void make_dirty();
	void make_not_dirty();

private:
	bool valid;
	bool dirty;
	int tag;
	bool LRU;
};

#endif // BLOCK_H
