/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	cpp file for class block													*
*																							*
*File Name: block.cpp																		*
*Date: 02/21/2016																			*
*********************************************************************************************/

#include "block.h"
#include <iostream>
using namespace std;
block::block()
{
	valid = false;
	tag = 0;
	cout << " false " << '\n';
}

void block::validate()
{
	valid = true;
}

void block::invalidate()
{
	valid = false;
}

bool block::check_valid()
{
	return valid;
}

void block::set_tag(int x)
{
	tag = x;
}


int block::read_tag()
{
	return tag;
}

bool block::read_LRU()
{
	return LRU;
}

void block::write_LRU(bool d)
{
	LRU = d;
}

bool block::check_dirty()
{
	return dirty;
}

void block::make_dirty()
{
	dirty = true;
}

void block::make_not_dirty()
{
	dirty = false;
}