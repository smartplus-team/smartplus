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

///@file state_variables_M.cpp
///@brief State variables of a mechanical material, in a defined coordinate system:
///@version 1.0

#include <iostream>
#include <fstream>
#include <assert.h>
#include <armadillo>
#include <smartplus/Libraries/Phase/state_variables.hpp>
#include <smartplus/Libraries/Phase/state_variables_M.hpp>
#include <smartplus/parameter.hpp>
#include <smartplus/Libraries/Maths/rotation.hpp>

using namespace std;
using namespace arma;

namespace smart{

//=====Private methods for state_variables===================================

//=====Public methods for state_variables============================================

/*!
  \brief default constructor
*/

//-------------------------------------------------------------
state_variables_M::state_variables_M() : state_variables(), sigma_in(6), sigma_in_start(6), Wm(4), Wm_start(4), L(6,6), Lt(6,6)
//-------------------------------------------------------------
{
    sigma_in = zeros(6);
    sigma_in_start = zeros(6);
    
    Wm = zeros(4);
    Wm_start = zeros(4);
    
	L = zeros(6,6);
	Lt = zeros(6,6);
}

/*!
  \brief Constructor with parameters
  \n\n
  \f$ \textbf{Examples :} \f$ \n
*/

//-------------------------------------------------------------
state_variables_M::state_variables_M(const vec &mEtot, const vec &mDEtot, const vec &msigma, const vec &msigma_start, const mat &mF0, const mat &mF1, const vec &msigma_in, const vec &msigma_in_start, const double &mT, const double &mDT, const int &mnstatev, const vec &mstatev, const vec &mstatev_start, const vec &mWm, const vec& mWm_start, const mat &mL, const mat &mLt) : state_variables(mEtot, mDEtot, msigma, msigma_start, mF0, mF1, mT, mDT, mnstatev, mstatev, mstatev_start), sigma_in(6), sigma_in_start(6), Wm(4), Wm_start(4), L(6,6), Lt(6,6)
//-------------------------------------------------------------
{

    assert (msigma_in.size() == 6);
    assert (msigma_in_start.size() == 6);
    
    assert (mWm.size() == 4);
    assert (mWm_start.size() == 4);
    
	assert (mL.n_rows == 6);
	assert (mL.n_cols == 6);
	assert (mLt.n_rows == 6);
	assert (mLt.n_cols == 6);	

    sigma_in = msigma_in;
    sigma_in_start = msigma_in_start;
    
    Wm = mWm;
    Wm_start = mWm_start;
    
	L = mL;
	Lt = mLt;
}

/*!
  \brief Copy constructor
  \param s state_variables object to duplicate
*/

//------------------------------------------------------
state_variables_M::state_variables_M(const state_variables_M& sv) : state_variables(sv), sigma_in(6), sigma_in_start(6), Wm(4), Wm_start(4), L(6,6), Lt(6,6)
//------------------------------------------------------
{
    sigma_in = sv.sigma_in;
    sigma_in_start = sv.sigma_in_start;
    
    Wm = sv.Wm;
    Wm_start = sv.Wm_start;
    
	L = sv.L;
	Lt = sv.Lt;
}

/*!
  \brief Destructor

  Deletes statev_variables, the vectors and matrix, and table statev if nstatev is not null.
*/

//-------------------------------------
state_variables_M::~state_variables_M()
//-------------------------------------
{

}

/*!
  \brief Standard operator = for state_variables
*/

//----------------------------------------------------------------------
state_variables_M& state_variables_M::operator = (const state_variables_M& sv)
//----------------------------------------------------------------------
{
	Etot = sv.Etot;
	DEtot = sv.DEtot;
	sigma = sv.sigma;
	sigma_start = sv.sigma_start;
    F0 = sv.F0;
    F1 = sv.F1;
    sigma_in = sv.sigma_in;
    sigma_in_start = sv.sigma_in_start;
	L = sv.L;
	Lt = sv.Lt;
    T = sv.T;
    DT = sv.DT;
    Wm = sv.Wm;
    Wm_start = sv.Wm_start;
    
    nstatev = sv.nstatev;
    statev = sv.statev;
    statev_start = sv.statev_start;

	return *this;

}

//----------------------------------------------------------------------
state_variables_M& state_variables_M::copy_fields_M(const state_variables_M& sv)
//----------------------------------------------------------------------
{
	Etot = sv.Etot;
	DEtot = sv.DEtot;
	sigma = sv.sigma;
	sigma_start = sv.sigma_start;
    F0 = sv.F0;
    F1 = sv.F1;
	sigma_in = sv.sigma_in;
    sigma_in_start = sv.sigma_in_start;
	L = sv.L;
	Lt = sv.Lt;
    T = sv.T;
    DT = sv.DT;
    Wm = sv.Wm;
    Wm_start = sv.Wm_start;

	return *this;

}

//-------------------------------------------------------------
void state_variables_M::update(const vec &mEtot, const vec &mDEtot, const vec &msigma, const vec &msigma_start, const mat &mF0, const mat &mF1, const vec &msigma_in, const vec &msigma_in_start, const double &mT, const double &mDT, const int &mnstatev, const vec &mstatev, const vec &mstatev_start,  const vec &mWm, const vec &mWm_start, const mat &mL, const mat &mLt)
//-------------------------------------------------------------
{
    state_variables::update(mEtot, mDEtot, msigma, msigma_start, mF0, mF1, mT, mDT, mnstatev, mstatev, mstatev_start);

    assert (msigma_in.size() == 6);
    assert (msigma_in_start.size() == 6);
    
    assert (mWm.size() == 4);
    assert (mWm_start.size() == 4);
    
    assert (mL.n_rows == 6);
    assert (mL.n_cols == 6);
    assert (mLt.n_rows == 6);
    assert (mLt.n_cols == 6);
    
    sigma_in = msigma_in;
    sigma_in_start = msigma_in_start;
    
    Wm = mWm;
    Wm_start = mWm_start;
    
    L = mL;
    Lt = mLt;
}
    
//-------------------------------------------------------------
void state_variables_M::to_start()
//-------------------------------------------------------------
{
    state_variables::to_start();
    sigma_in = sigma_in_start;
    Wm = Wm_start;
}

//-------------------------------------------------------------
void state_variables_M::set_start()
//-------------------------------------------------------------
{
    state_variables::set_start();
    sigma_in_start = sigma_in;
    Wm_start = Wm;
}
        
//----------------------------------------------------------------------
state_variables_M& state_variables_M::rotate_l2g(const state_variables_M& sv, const double &psi, const double &theta, const double &phi)
//----------------------------------------------------------------------
{
    
    state_variables::rotate_l2g(sv, psi, theta, phi);
    
    sigma_in = sv.sigma_in;
    sigma_in_start = sv.sigma_in_start;
    
    Wm = sv.Wm;
    Wm_start = sv.Wm_start;
    
	L = sv.L;
	Lt = sv.Lt;
    
  	if(fabs(phi) > iota) {
        sigma_in = rotate_stress(sigma_in, -phi, axis_phi);
        sigma_in_start = rotate_stress(sigma_in_start, -phi, axis_phi);
		L = rotateL(L, -phi, axis_phi);
		Lt = rotateL(Lt, -phi, axis_phi);
	}
  	if(fabs(theta) > iota) {
        sigma_in = rotate_stress(sigma_in, -theta, axis_theta);
        sigma_in_start = rotate_stress(sigma_in_start, -theta, axis_theta);
		Lt = rotateL(Lt, -theta, axis_theta);
		L = rotateL(L, -theta, axis_theta);
	}
	if(fabs(psi) > iota) {
        sigma_in = rotate_stress(sigma_in, -psi, axis_psi);
        sigma_in_start = rotate_stress(sigma_in_start, -psi, axis_psi);
		Lt = rotateL(Lt, -psi, axis_psi);
		L = rotateL(L, -psi, axis_psi);        
	}
    
	return *this;
}

//----------------------------------------------------------------------
state_variables_M& state_variables_M::rotate_g2l(const state_variables_M& sv, const double &psi, const double &theta, const double &phi)
//----------------------------------------------------------------------
{

    state_variables::rotate_g2l(sv, psi, theta, phi);
    
    sigma_in = sv.sigma_in;
    sigma_in_start = sv.sigma_in_start;
    
    Wm = sv.Wm;
    Wm_start = sv.Wm_start;

    L = sv.L;
    Lt = sv.Lt;
    
  	if(fabs(psi) > iota) {
        sigma_in = rotate_stress(sigma_in, psi, axis_psi);
        sigma_in_start = rotate_stress(sigma_in_start, psi, axis_psi);
		L = rotateL(L, psi, axis_psi);
		Lt = rotateL(Lt, psi, axis_psi);
	}			
	if(fabs(theta) > iota) {
        sigma_in = rotate_stress(sigma_in, theta, axis_theta);
        sigma_in_start = rotate_stress(sigma_in_start, theta, axis_theta);
		L = rotateL(L, theta, axis_theta);
		Lt = rotateL(Lt, theta, axis_theta);
	}
	if(fabs(phi) > iota) {
        sigma_in = rotate_stress(sigma_in, phi, axis_phi);
        sigma_in_start = rotate_stress(sigma_in_start, phi, axis_phi);
		L = rotateL(L, phi, axis_phi);
		Lt = rotateL(Lt, phi, axis_phi);
    }
    
	return *this;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& s, const state_variables_M& sv)
//--------------------------------------------------------------------------
{
	s << "Etot: \n" << sv.Etot << "\n";
	s << "DEtot: \n" << sv.DEtot << "\n";
	s << "sigma: \n" << sv.sigma << "\n";
	s << "sigma_start: \n" << sv.sigma_start << "\n";
    s << "F0: \n" << sv.F0 << "\n";
    s << "F1: \n" << sv.F1 << "\n";
    s << "sigma_in: \n" << sv.sigma_in << "\n";
    s << "sigma_in_start: \n" << sv.sigma_in_start << "\n";    
    s << "T: \n" << sv.T << "\n";
    s << "DT: \n" << sv.DT << "\n";
    s << "Wm: \n" << sv.Wm << "\n";
    s << "Wm_start: \n" << sv.Wm_start << "\n";
	s << "L: \n" << sv.L << "\n";
	s << "Lt: \n" << sv.Lt << "\n";
	s << "\n";

    s << "nstatev: \n" << sv.nstatev << "\n";
    if (sv.nstatev) {
        s << "statev: \n";
        s << sv.statev.t();
        s << "\n";
        s << sv.statev_start.t();
        s << "\n";
    }
    
	return s;
}

} //namespace smart
