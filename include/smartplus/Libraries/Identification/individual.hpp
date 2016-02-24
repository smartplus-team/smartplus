/* This file is part of SMART+ private.
 
 Only part of SMART+ is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This file is not be distributed under the terms of the GNU GPL 3.
 It is a proprietary file, copyrighted by the authors
 */

///@file individual.hpp
///@brief individual for genetic algorithm (among others)
///@author Chemisky & Despringre
///@version 1.0

#pragma once
#include <iostream>
#include <armadillo>

namespace smart{

//======================================
class individual
//======================================
{
	private:

	protected:

	public :
		int np;
        double cout;
		int id;
		int rank;		
        arma::vec p;
		
		individual(); 	//default constructor
		individual(const int&,const int&);	//constructor - allocates memory for statev
		individual(const individual&);	//Copy constructor
		~individual();
		
		int dimp() const {return np;}       // returns the number of parameters

		void construct();

		virtual individual& operator = (const individual&);
		
        friend std::ostream& operator << (std::ostream&, const individual&);
};
    
} //namespace smart