/**
 * @file dsal.cpp
 * @version 1.0
 * @since Jun, 12.
 * @date May, 12.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Dictionary ADT using an Sorted array
 */


#include "dictionary.hpp"
	/*!
	 * 	@brief Auxiliar binary search for an key.
	 * 	@param _x The key.
	 */
template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search ( const Key & _x ) const {

	auto begin = this->mpt_Data;
	auto begin_back = begin;
	auto end = this->mpt_Data + this->mi_Length;
	KeyComparator comp;

	while(begin <= end){

		auto mid = begin + (end-begin)/2;

		if( comp (mid->id, _x) == 0 and comp(_x, mid->id) == 0)
			return mid - begin_back;

		else if (comp (mid->id, _x)){

			begin = mid + 1;
		}

		else {
			end = mid - 1;
		}
	}

	return -1;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert 
	( const Key & _newKey, const Data & _newInfo ) {

	int index = _search(_newKey);
	
	if(index != -1){ return false;}
	
	if(this->mi_Length == this->mi_Capacity)
		this->reserve(this->mi_Length *2);

	NodeAL *pivot;
	int distance;
	KeyComparator comp;
	for (auto i = this->mpt_Data;  i < this->mpt_Data + this->mi_Length; ++i) {
		if(comp(_newKey,i->id)){
			pivot = i;
			distance = i - this->mpt_Data;
			
			for (int i = this->mi_Length; i > distance; --i) {
				this->mpt_Data[i] =  this->mpt_Data[i-1]; 
			}

			*pivot = NodeAL(_newKey,_newInfo);
			this->mi_Length++;
			return true;
		}
	}
	this->mpt_Data[this->mi_Length++] = NodeAL(_newKey,_newInfo);

	return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::successor( const Key & _x , Key & _y ) const{

	int index = _search(_x);
	if(index == this->mi_Length-1) return false;
	_y = this->mpt_Data[index+1].id;
	return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor( const Key & _x , Key & _y ) const{

	int index = _search(_x);
	if(index == 0) return false;
	_y = this->mpt_Data[index-1].id;
	return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove( const Key & _x, Data & _D ) {


	int index = _search(_x);
	if (index == -1) return false;
	
	if(this->mi_Length < 1){
		throw std::runtime_error("Can't remove elements from empty dict");
	}
	
	_D = this->mpt_Data[index].info;
	
	std::copy(this->mpt_Data+index+1,
			this->mpt_Data+this->mi_Length,this->mpt_Data+index);


	this->mi_Length--;
	return true;
}
