/**
 * @file dal.cpp
 * @version 1.0
 * @since Jun, 12.
 * @date May, 14.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Dictionary ADT using an unsorted array
 */

#include "dictionary.hpp"

/*!
 * 	@brief Auxiliar linear search for an key.
 * 	@param _x The key.
 */
template < typename Key, typename Data, typename KeyComparator >
int DAL<Key, Data, KeyComparator>::_search( const Key & _x ) const{
	
	for (int i = 0; i < mi_Length; ++i)
		if ( mpt_Data[i].id == _x )
			return i;

	return -1;
}

/*! 
 *  @brief Class constructor, allocates in mpt_Data a vector with size = "_MaxSz".
 *	@param _MaxSz The capacity Size.
 */
template < typename Key, typename Data, typename KeyComparator >
DAL<Key, Data, KeyComparator>::DAL( int _MaxSz ){
	
	mi_Capacity = _MaxSz;
	mi_Length = 0;
	mpt_Data = new NodeAL[ _MaxSz ];
}


//! @brief Class Destructor, destructs the memory pointed by mpt_Data.
template < typename Key, typename Data, typename KeyComparator >
DAL<Key, Data, KeyComparator>::~DAL(){
	
	delete[] mpt_Data;
}


/*!	@brief  Remove the info related to the "_x" key.
 *  @param  _x The key
 *  @return True if the key was removed successfuly; False otherwise.
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::remove( const Key & _x,  Data & _D ){

	//! Verifies if the array is empty
	if( empty() )
	{

//		std::cerr << "\n@remove ERROR: Cannot remove an element from an empty Dictionary!\n";
		return false;
	}

	int indice = _search( _x );

	//! Verifies if there is any data with the key param.
	if( indice == -1 )
	{
//		std::cerr << "\n@remove ERROR: Key not found on the Dictionary!\n";
		return false;
	}
	_D = mpt_Data[indice].info;
	mpt_Data[ indice ] = mpt_Data[--mi_Length]; //!< Removing data from the array 

	return true;
}

/*!
 *  @brief  Serch the key's "_x" data
 *  @param  _x The key
 *  @param  _s The information
 *  @return True if the key was found; False otherwise.
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::search( const Key & _x, Data & _s ) const{

	int indice = _search( _x );

	if( indice == -1 )
		return false;

	_s = mpt_Data[ indice ].info; //!< Element finding
	return true;
}

/*!
 *  @brief  Resizes the array, helping insertion.
 *  @param  new_capacity The new Vector capacity
 */
template < typename Key, typename Data, typename KeyComparator >
void DAL<Key, Data, KeyComparator>::reserve( size_t new_capacity ){

	if( new_capacity <= mi_Capacity ) return; // Nothing to do 

	mi_Capacity = new_capacity;
	NodeAL * tmp = new NodeAL[new_capacity];
	std::copy(mpt_Data, mpt_Data + mi_Length, tmp);

	delete [] mpt_Data;

	mpt_Data = new NodeAL[mi_Capacity];
	for( auto i(0); i < mi_Length; i++ ){
		*(mpt_Data+i) = *(tmp+i);
	}

	delete [] tmp;
}

/*!
 *  @brief  Inserts the Key and info on the array (only if not empty of if the key does not exists yet in the array).
 *  @param  _newKey  The new key
 *  @param  _newInfo The new data
 *  @return True se a inserção foi bem sucedida, false caso contrário.
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::insert( const Key & _newKey, const Data & _newInfo ){

	//<! Verifies if the array is full
	if( full() ){

		/*// std::cout << "\t@insert ERROR: Cannot insert a new element in a full Dictionary!\n";*/
		reserve(mi_Capacity * 2 );		
		NodeAL new_node( _newKey, _newInfo ); 
		mpt_Data[mi_Length++] = new_node; //!< Inseting the data in the array
		return true;
	}
	
	//! If there is an element in the Dictionaray with this key, do not insert it
	if( not (_search( _newKey ) == -1) ) {

//		// std::cout << "\n@insert ERROR: Key already exists on the Dictionary!\n";
		return false;
	}
 
	NodeAL new_node( _newKey, _newInfo ); 
	mpt_Data[mi_Length++] = new_node; //!< Inseting the data in the array

	return true;
}

/*!
 *  @brief Recovers the smaller key in the dictionary.
 *  @return The smaller key.
 */
template < typename Key, typename Data, typename KeyComparator >
Key DAL<Key, Data, KeyComparator>::min( void ) const{

	if(empty()) throw std::out_of_range("Empty dict");
	KeyComparator compare; //<! Comparation functor
	
	Key min = mpt_Data[0].id; //<! A min value

	for (int i = 1; i < mi_Length; ++i)
		if( compare( mpt_Data[i].id, min ) )
			min = mpt_Data[i].id; //!< If there is a key smaller than "min", min becomes it

	return min;
}

/*!
 *  @brief Recovers the bigger key in the dictionary.
 *  @return The bigger key.
 */
template < typename Key, typename Data, typename KeyComparator >
Key DAL<Key, Data, KeyComparator>::max( void ) const{


	if(empty()) throw std::out_of_range("Empty dict");
	KeyComparator compare; //!< Comparation functor
	
	Key max = mpt_Data[0].id;//!< A max value

	for (int i = 1; i < mi_Length; ++i)
		if( compare( max, mpt_Data[i].id ) )
			max = mpt_Data[i].id; //!< If there is a key smaller than "min", min becomes it

	return max;
}

/*!
 *  @brief Recovers in "_y" the sucessor key to "_x".
 *  @return True If it does exists; False otherwise.
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::successor( const Key & _x , Key & _y ) const{

	int minimum = _x;
	for(int i = 0; i < mi_Length; i++)
	{
		if(mpt_Data[i].id > _x)
			if(mpt_Data[i].id < minimum)
				minimum = mpt_Data[i].id;
	}

	if(minimum == _x) return false;

	else{
		_y = minimum;
		return true;
	}
}

/*!
 *  @brief Recovers in "_y" the predecessor key to "_x".
 *  @return True If it does exists; False otherwise.
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::predecessor( const Key & _x , Key & _y ) const{

	int maximum = _x;
	for(int i = 0; i < mi_Length; i++)
	{
		if(mpt_Data[i].id < _x)
			if(mpt_Data[i].id > maximum)
				maximum = mpt_Data[i].id;
	}

	if(maximum == _x) return false;

	else{
		_y = maximum;
		return true;
	}
}

/*! 
 *  @brief Tells if the dictionary is full or not.
 *	@return True if it is full; False otherwise. 
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::full() const{

	return ( mi_Capacity == mi_Length );
}

/*! 
 *  @brief Tells if the dictionary is empty or not.
 *	@return True if it is empty; False otherwise. 
 */
template < typename Key, typename Data, typename KeyComparator >
bool DAL<Key, Data, KeyComparator>::empty() const{

	return (  mi_Length == 0 );
}

/*! 
 *  @brief Tells the dictionary capacity.
 *	@return The capacity. 
 */
template < typename Key, typename Data, typename KeyComparator >
int DAL<Key, Data, KeyComparator>::capacity( void ) const{

	return mi_Capacity;
}

/*! 
 *  @brief Tells the number of elements in the dictionary.
 *	@return The lenght. 
 */
template < typename Key, typename Data, typename KeyComparator >
int DAL<Key, Data, KeyComparator>::size( void ) const{

	return mi_Length;
}

