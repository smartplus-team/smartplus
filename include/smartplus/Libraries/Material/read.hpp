/* This file is part of SMART+.
 
 SMART+ is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SMART+ is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SMART+.  If not, see <http://www.gnu.org/licenses/>.
 
 */

///@file read.hpp
///@brief To read from NpeaksX.dat
///@version 1.0

#pragma once
#include <armadillo>
#include <string>
#include "ODF.hpp"
#include "PDF.hpp"

namespace smart{
    
/// Function that reads the output parameters
    void read_peak(ODF &, const std::string &, const std::string &);
    
    void read_peak(PDF &, const std::string &, const std::string &);

} //namespace smart
