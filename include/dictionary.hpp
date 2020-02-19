/**
 * @file dictionary.hpp
 * @version 1.0
 * @since Jun, 12.
 * @date Jun, 21.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Dictionary ADT
 */

#ifndef _DICTIONARY_HPP_
#define _DICTIONARY_HPP_

#include <iostream>
#include <string>
#include <iterator>
#include <functional>

//! @brief Dictionary with Array List 
template < typename Key, typename Data, typename KeyComparator = std::less<int> >
class DAL{

protected:

//	using Key = int ; // Alias to the key
//	using Data = std::string ; // Alias to the data
	
	struct NodeAL {  
		Key id;    // The key is an simple integer
		Data info; // A string

		NodeAL( Key k_= Key(), Data d_= Data() ) : id(k_), info(d_) {/*Empty*/}
	};
	static const int SIZE = 50; //<! List's default size
	NodeAL * mpt_Data ; 		//<! Storage area: vector dynamically allocated.
	int mi_Length;              //<! List's current size
	int mi_Capacity;            //<! Storage maximum capacity
	//<! Node related to the key pair.

	/*!
	 * 	@brief Auxiliar linear search for an key.
	 * 	@param _x The key.
	 */
	int _search( const Key & _x ) const;

public:

	/*! 
	 *  @brief Class constructor, allocates in mpt_Data a vector with size = "_MaxSz".
	 *	@param _MaxSz The capacity Size.
	 */
	DAL( int _MaxSz = SIZE );

	//! @brief Class Destructor, destructs the memory pointed by m_data
	virtual ~DAL ( void );


	/*!
    \brief  Copy Constructor
    */
    DAL( const DAL &obj ):
		mi_Length(obj.mi_Length),
		mi_Capacity(obj.mi_Capacity),
		mpt_Data(new NodeAL[obj.mi_Length])
	{
        *this = obj;
    }

    /*!
    \brief assignment operator
    */
    DAL& operator=( const DAL &obj ){
        if( this != &obj ){
            
			this->mi_Length = obj.mi_Length;
            reserve(obj.mi_Capacity);
			
            std::copy( obj.mpt_Data, obj.mpt_Data + obj.mi_Length, this->mpt_Data );

        }
        return *this;
}
	/*!
	 *  @brief  Remove the info related to the "_x" key.
	 *  @param  _x The key
	 *  @return True if the key was removed successfuly; False otherwise.
	 */
	bool remove( const Key & _x,  Data & _d );

	/*!
	 *  @brief  Serch the key's "_x" data
	 *  @param  _x The key
	 *  @param  _s The information
	 *  @return True if the key was found; False otherwise.
	 */
	bool search( const Key & _x, Data & _s ) const;

	/*!
	 *  @brief  Inserts the Key and info on the array (only if not empty of if the key does not exists yet in the array).
	 *  @param  _newKey  The new key
	 *  @param  _newInfo The new data
	 *  @return True se a inserção foi bem sucedida, false caso contrário.
	 */
	bool insert( const Key & _newKey, const Data & _newInfo ); // Insere na lista.

	/*!
	 *  @brief  Resizes the array, helping insertion.
	 *  @param  new_capacity The new Vector capacity
	 */
	void reserve( size_t new_capacity );	

	/*!
	 *  @brief Recovers the smaller key in the dictionary.
	 *  @return The smaller key.
	 */
	Key min( void ) const;
	
	/*!
	 *  @brief Recovers the bigger key in the dictionary.
	 *  @return The bigger key.
	 */
	Key max( void ) const;

	/*!
	 *  @brief Recovers in "_y" the successor key to "_x".
	 *  @return True If it does exists; False otherwise.
	 */
	bool successor( const Key & _x , Key & _y ) const;

	/*!
	 *  @brief Recovers in "_y" the predecessor key to "_x".
	 *  @return True If it does exists; False otherwise.
	 */
	bool predecessor( const Key & _x , Key & _y ) const;

	/*! 
	 *  @brief Tells if the dictionary is full or not.
	 *	@return True if it is full; False otherwise. 
	 */
	bool full( void ) const;

	/*! 
	 *  @brief Tells if the dictionary is empty or not.
	 *	@return True if it is empty; False otherwise. 
	 */
	bool empty( void ) const;

	/*! 
	 *  @brief Tells the dictionary capacity.
	 *	@return The capacity. 
	 */
	int capacity( void ) const;

	/*! 
	 *  @brief Tells the number of elements in the dictionary.
	 *	@return The lenght. 
	 */
	int size( void ) const;

	/*! @brief Sends back to the output stream an ASCII representation for the list.*/
	inline friend
	std::ostream & operator<<( std::ostream & _os , const DAL & _oList ){
		_os << "[ ";
		for ( int i (0); i < _oList.mi_Length; ++i )
			_os << " ID: " << _oList.mpt_Data[ i ].id << ", INFO: "
			    << _oList.mpt_Data[ i ].info << " ";
		_os << "]";
		return _os;
	}
};

//! @brief Dictionary with Sorted Array List 
template < typename Key, typename Data, typename KeyComparator = std::less<int> >
class DSAL : public DAL< Key, Data, KeyComparator > /*heritage*/ {

	using NodeAL = typename DAL< Key, Data, KeyComparator >::NodeAL;

private:

	/*!
	 * 	@brief Auxiliar linear search for an key.
	 * 	@param _x The key.
	 */
	int _search ( const Key & _x ) const ;

public:

	/*! 
	 *  @brief DSAL's copy constructor 
	 */
	DSAL ( int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE ) : DAL< Key, Data, KeyComparator > ( _MaxSz ) { /* Empty */ };

	//DSAL ( void ) : DAL< Key, Data, KeyComparator > ( void ) { /*Empty*/ }

	virtual ~DSAL( void ) { /* Empty */ };

/*------------------------------ Overwriting --------------------------------*/ 
 
 	/*!
	 *  @brief Removes the Info realted to the "_x" key.
	 *  @param _x The key
	 * 	@return True if the remove happened successfully; False otehrwise.
	 *	@note
	 */
	bool remove( const Key & _x,  Data & _d );

	/*!
	 *  @brief Inserts an Key and infor in the array 
	 *  @param _newKey The new Key
	 *  @param _newInfo The new info
	 *  @return True if the insetion happened successfully; False otehrwise.
	 *	@note
	 */
	bool insert( const Key & _novaId , const Data & _novaInfo );

	/*!
	 *  @brief Recovers the smaller key in the dictionary.
	 *  @return The smaller key.
	 * 	@note As the array is sorted now, it returns the first element in the array.
	 */
	Key min( void ) const { 
		if(this->mi_Length < 1) throw std::out_of_range("Empty Dict");
		return this->mpt_Data[0].id ; 
	}
	
	/*!
	 *  @brief Recovers the bigger key in the dictionary.
	 *  @return The bigger key.
	 * 	@note As the array is sorted now, it returns the last element in the array.
	 */
	Key max( void ) const { 
		if(this->mi_Length < 1) throw std::out_of_range("Empty Dict");
		return this->mpt_Data[this->mi_Length-1].id;
	}

	/*!
	 *  @brief Recovers in "_y" the successor key to "_x".
	 *  @return True If it does exists; False otherwise.
	 *	@note
	 */
	bool successor( const Key & _x , Key & _y ) const;

	/*!
	 *  @brief Recovers in "_y" the predecessor key to "_x".
	 *  @return True If it does exists; False otherwise.
	 * 	@note
	 */
	bool predecessor( const Key & _x , Key & _y ) const;

};

#include "dal.hpp"
#include "dsal.hpp"

#endif
