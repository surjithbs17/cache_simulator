/********************************************************************************************
*Author Name:	Surjith Bhagavath Singh														*
*Description:	Cache simulator, gets the input as cache size, block size, word size,		*
*				associativity and data trace file and gives the output of number of hits	*
*				and misses.																	*
*																							*
*Variables has to be modified in #define table in main.cpp file.							*
*CPP Files		: main.cpp, cache.cpp, set_blocks.cpp, block.cpp							*
*Header files	: cache.h, set_blocks.h, block.h											*
*																							*
*File Name: main.cpp																		*
*Date: 02/21/2016																			*
*********************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "block.h"
#include "cache.h"
#include "set_blocks.h"


/**********************************  #define table  ****************************************/

#define FILENAME "data.txt"
#define DATATRACEMAXLENGTH 10000
#define ASSOCIATIVITY 32
#define CACHESIZE 16384
#define BLOCKSIZE 4
#define WORDSIZE 4
#define WRITETHROUGH true
#define LRU_CLEARANCE_FREQ 10

using namespace std;


/**********************************  global variables  ****************************************/

char Re_Wr;
char *arr;
string address;
int *R_W;
long long int *addr;
int num_lines;
int hit,miss = 0;
int r_hit,r_miss,w_hit,w_miss = 0;
int write_back = 0;


/********************************************************************************************
*Function Name	: fileread()																*
*Return value	: none																		*
*Description:	reads the data trace file and stores the address in addr[] array			*
*				and check whether it is read or write and stores a flag number 1/0 in R_W[]	*
*				array																		*
*																							*
*File name: main.cpp																		*
*Date: 02/21/2016																			*
*********************************************************************************************/

void fileread()
{
	R_W = (int *)malloc(sizeof(int)*(DATATRACEMAXLENGTH + 1));
	addr = (long long int *) malloc(sizeof(long long int)*(DATATRACEMAXLENGTH + 1));
	ifstream input_file(FILENAME);				//opening file as input
	int i = 0;

	while (input_file >> Re_Wr >> address)		//looping till EOF
	{
		if (Re_Wr == 'R')						//storing the condition R/W
			R_W[i] = 1;
		else if (Re_Wr == 'W')
			R_W[i] = 0;
		addr[i] = std::stoll(address, NULL, 16);	//converting string to long long int address
		
		//cout << i << ' ' << R_W[i] << ' ' << address << '\n';	//feedback cout
		i++;					//loop variable
	}

	num_lines = i;				//saving the number of lines
}


/********************************************************************************************
*Function Name	: main()																	*
*Return value	: none																		*
*Description	: main function does the simulation operation, by allocating cache classes	* 
*				  according to #define table and simulating the cache using the trace file	*
*																							*
*																							*
*File name: main.cpp																		*
*Date: 02/21/2016																			*
*********************************************************************************************/


void main()
{
	fileread();
	cout << "Number of Lines : " << num_lines << '\n';


	
	
	bool W_T = WRITETHROUGH;
	int cache_size = CACHESIZE;
	int associativity = ASSOCIATIVITY;
	int cache_block_size;
	int word_size = WORDSIZE;			//in bytes
	int num_of_words = BLOCKSIZE;		//num of words in a block
	int block_word_size = num_of_words*word_size;
	cache_block_size = cache_size / (associativity*block_word_size);
	int j = cache_block_size;
	int index_size = 0;
	int offset = 0;
	int k = block_word_size;


	for (index_size = 0; j > 1; index_size++)				//caculating index size
	{ 
		j = j / 2;
	}
	for (offset = 0; k > 1; offset++)				//calculating offset size
	{
		k = k / 2;
	}
	//cout << "index size " << index_size << "offset" <<offset <<'\n';

	cache caches(cache_block_size,associativity);		//allocating cache class according to user input
	caches.cache_alloc();
	cout << "\nCache Allocated Successfully\n";
	
	
	for (int i = 0; i < num_lines; i++)					//looping for wach line in trace file
	{
		if (i % LRU_CLEARANCE_FREQ == 0)								//LRU bit clearance
		{
			for (int s = 0; s < index_size; s++)
			{
				for (int t = 0; t < associativity; t++)
				{
					caches.wr_bl_lru(s, t, false);
				}
				
			}
		}

		long long int temp = addr[i];					//storing the address in temp variable to do index,tag extraction
		long long int temp_offset, temp_tag, temp_index;
		int curr_index, curr_tag, curr_offset;
		
		long long int mask = ((1 << (offset)) - 1);
		temp_offset = (temp) & mask;
		curr_offset = temp_offset;
		mask = (1 << ((offset+index_size) - offset)) - 1;
		temp_index = (temp >> offset) & mask;
		curr_index = temp_index;
		mask = (1 << (32 - (offset + index_size))) - 1;
		temp_tag = (temp >> (offset+index_size)) & mask;
		curr_tag = temp_tag;
		//cout << "temp_offset " << hex << temp_offset << " temp_index " << hex << temp_index << " addr[i] "<< hex << addr[i]<< " temp_tag " << hex <<temp_tag << " mask " <<hex << mask<<'\n';
		

		if ((R_W[i] == 1) || (R_W[i]==0))		//checking whether it is read or write
		{
			int curr_block = 0;
			bool mis_match = false;				//initializing flags to default value
			bool invalid = false;

			for (; curr_block != (associativity-1);)	//looping through the blocks of same index
			{
				if (mis_match || invalid)		//checking whether there is a mismatch in tag or invalid block 
				{
					curr_block++;					
				}

				if (caches.read_cache(curr_index).read_block(curr_block).check_valid())		//checking valid bit
				{
					if (caches.read_cache(curr_index).read_block(curr_block).read_tag() == curr_tag)	//checking tag
					{
						if (R_W[i] == 1)			//checking for read
						{
							hit++;						//hit
							r_hit++;					//incrementing read hit
							break;
						}
						if (R_W[i] == 0)		//checking for write
						{
							if (W_T)			//checking for write_through
							{
								hit++;				//hit
								w_hit++;			//incrementing write hit
								break;
							}
							else				//write back condition
							{
								if (caches.read_cache(curr_index).read_block(curr_block).check_dirty())		//dirty bit check
								{
									write_back++;			//increment write back count
									hit++;					//hit
									w_hit++;				//incrementing write hit
									caches.write_cache(curr_index, curr_block, curr_tag, true, true, false);	//resetting dirty bit
									break;
								}
								else			//not dirty condition
								{
									caches.write_cache(curr_index, curr_block, curr_tag, true, true, true);	//set dirty
									hit++;					//hit
									w_hit++;				//incrementing write hit
									break;
								}
							}
								
						}
					}
					else
						mis_match = true;			//setting mismatatch flag (i.e tag mismatch)
				}
				else					//invalid condition
					{
						invalid = true;
						if (curr_block == (associativity-1))		//checking for it is in the final block of the set
						{
							miss++;									//miss
							if (R_W[i] == 1)						//checking read condition
							{
								r_miss++;							//incrementing read miss
								
							}
							else						//write miss condition
							w_miss++;

							for (int p = 0; p < associativity; p++)		//LRU checking to replace a block in the cache
							{
								if (caches.read_cache(curr_index).read_block(p).read_LRU() == false)	//Not recently used condition (LRU=false)
								{
									caches.write_cache(curr_index, p, curr_tag, true, true,false);		//making LRU true and updating the cache
									break;
								}
								else if ((caches.read_cache(curr_index).read_block(p).read_LRU()) && (p == (associativity - 1)))	//checking all the blocks
								{
									caches.write_cache(curr_index, 0, curr_tag, true, true,false);		//replacing the first element of the set
									break;
								}
							}


						}


					}
				
			}
		}
		

	}
	cout << "\nTotal number of lines in Trace file : " << num_lines << '\n';
	cout << "\nTotal hit : " << hit << "\n\tRead hit : " << r_hit <<"\n\tWrite hit : "<< w_hit << "\nTotal miss : " << miss << "\n\tRead Miss : " << r_miss << " \n\tWrite miss : " << w_miss << '\n';

}
