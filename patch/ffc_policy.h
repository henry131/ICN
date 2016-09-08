/*
Implementation for Filer First Caching
-------------------------------------
Author: Henry Williams
Date Created: 2nd August 2016

Integration of multi-layered filtering technique (additional name cache)
with simple caching mechansims to reduce caching redundancy
e.g. FFC(p) -> FIx(p)
e.g. TFC -> LCD
e.g. WFC(p) -> LCD with a weak first filter 

 */
#ifndef FFC_POLICY_H_
#define FFC_POLICY_H_

#include "decision_policy.h"
#include "base_cache.h"
#include "lru_cache.h"
#include <iostream>
#include "error_handling.h"

class FFC: public DecisionPolicy
{
  public:
	FFC(uint32_t cSize, bool t = false, double f = 0):ncSize(cSize){
		init(t);
		if (f)
		{
				set_filter_p(f);
		}
	}

	FFC(double pc, uint32_t cSize):ncSize(cSize){
		//cout << "initializing FFC(" << pc << ") << endl;
		init(false);
		set_p(pc);	
	}				

	virtual void finish (int nodeIndex, base_cache* cache_p) {
		//Remove Name Cache once ended
		delete name_cache;	
	}

	// Function needs to be separate to allow for case when interest is satisfied from
	// cache - called by core_layer::handle_interest(ccn_interest)

	bool lookup_name_cache(chunk_t chunk)
	{
		//looking up in lru_cache (name_cache) updates LRU status
		if (name_cache->lookup_name(chunk))
		{
			// Update its position and return True.
			map<chunk_t, double>::iterator itHit = monitored_contents.find(chunk);
			if(itHit == monitored_contents.end())
			{
				cerr << "FFC - trying to update a non existing entry!\n";
				//exit(1);
			}
			monitored_contents[chunk] = SIMTIME_DBL(simTime());
			return true;
		}
		//Insert into name cache and return false
		else
		{ 
			if(current_size == ncSize)
			{
				chunk_t k = (name_cache->get_lru())->k;
				map<chunk_t, double>::iterator it = monitored_contents.find(k);
				if(it == monitored_contents.end())
				{
					cerr << simTime() << "Name Cache LRU # " << k << " is not present!\n";
					//exit(1);
				}
				else
				{
					monitored_contents.erase(k);
					current_size--;
				}
			}

			// Insert the new element inside the map
			map<chunk_t, double>::iterator it = monitored_contents.find(chunk);
			if(it == monitored_contents.end())
			{
				monitored_contents[chunk] = SIMTIME_DBL(simTime());
			}
			else
			{
				cerr << "FFC - The entry (" << chunk << ") is present despite the previous miss event!\n";
				//exit(1);
			}

			if(current_size < ncSize)
				current_size++;

			name_cache->store_name(chunk);
			return false;
		}
	}

	virtual bool data_to_cache(ccn_data * msg)
	{
		chunk_t chunk = msg->getChunk();
		// check if message is already in Name Cache
		if (lookup_name_cache(chunk))
		{
			//prob(p)-like random for FFC(p)
			if (p > 0)
			{
				double x = dblrand();
				if (x < p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			
			//LCD-like trickle effect for TFC
			if (trickle)
			{
				if (msg->getHops() == 1)
				{
					return true;
				}
				else
				{
					return false;	
				}
			}

			//default for FFC
			return true;
		}
		//Weak filter implementation for WFC(p)	
		else if (filter_p > 0)
		{
			double x = dblrand();
			if (x < filter_p)
			{
				//cout << "------> weak filter cache" << endl;
				return true;
			}
		}

		// Content not in name cache and not got through weak filter - dont cache
		// Added to name cache in lookup function
		return false;
		
	}

	void set_p (double prob){
		if (prob >= 0.0 && prob <= 1.0) {
			p = prob;
		}
		else {
			cerr << "Invalid ffc::p entry" << endl;
			exit(1);
		}
	}
	
	void set_filter_p (double prob){
		if (prob >= 0.0 && prob <= 1.0) {
			//cout << "---->  SETTING FILTER P TO " << prob << endl;
			filter_p = prob;
		}
		else {
			cerr << "Invalid ffc::filter_p entry" << endl;
			exit(1);
		}
	}

	double get_p () {return p;}

	void set_stable () {nc_stable = true;}

	lru_cache* name_cache;

    private:
	double p;
	double filter_p;
	map < chunk_t, double> monitored_contents;
	uint32_t ncSize;
	uint32_t current_size;
	bool nc_stable;
	bool trickle;
	void init (bool t) {
		// Create a new LRU cache that will act as a Name Cache.
		base_cache* bcPointer = new lru_cache();
		name_cache = dynamic_cast<lru_cache *> (bcPointer);
		// Set the size of the Name Cache.
		name_cache->set_size(ncSize);
		nc_stable = false;
		trickle = t;
		current_size = 0;
		p = 0;
		filter_p = 0;
	}
};
#endif
