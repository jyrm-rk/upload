/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once



#include <map>

#include "MergeManager.h"



namespace com

{

namespace pcbsys

{

namespace foundation

{

namespace collections

{



template<class TKey, class TValue, class Compare = std::less<TKey> > class fSortedList :

    public std::map<TKey, TValue, Compare>

{

  public:

    void Add(TKey key, TValue value)

    {

		std::map<TKey, TValue, Compare>::insert(typename fSortedList<TKey, TValue, Compare>::value_type(key, value));

    }



    void Remove(TKey key)

    {

		std::map<TKey, TValue, Compare>::erase(key);

    }



	void merge(fSortedList<TKey, TValue, Compare>& changes, MergeManager *pManager)

    {

		typename fSortedList<TKey, TValue, Compare>::iterator changeIterator;



        for (changeIterator = changes.begin(); changeIterator != changes.end(); changeIterator++)

        {
#ifdef OSX
			typename fSortedList<TKey, TValue>::iterator localIterator = fSortedList<TKey, TValue, Compare>::find(changeIterator->first);
#else

#ifdef __arm__       // Arm does not support this
			typename fSortedList<TKey, TValue>::iterator localIterator = fSortedList<TKey, TValue, Compare>::find(changeIterator->first);
#else
			typename fSortedList<TKey, TValue, Compare>::iterator localIterator = fSortedList<TKey, TValue, Compare>::find(changeIterator->first);
#endif
#endif

            if (localIterator == this->end())

            {

                // its a newly added one

                Add(changeIterator->first, changeIterator->second);

                pManager->added(changeIterator->second);

            }



            else

            {

                // merge the entry, it exists so check modifications

                pManager->merge(localIterator->second, changeIterator->second);

            }

        }



        for (changeIterator = this->begin(); changeIterator != this->end(); )

        {

            if (changes.find(changeIterator->first) == changes.end())

            {

                // its been removed

                TKey key = changeIterator->first;
                TValue value = changeIterator->second;

                changeIterator++;

                Remove(key);

                pManager->deleted(value);

            }

            else
                changeIterator++;

        }
    }



};



}

}

}

}

