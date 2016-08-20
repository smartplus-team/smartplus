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

///@file state_variables_T.cpp
///@brief State variables of a phase, in a defined coordinate system:
///@version 1.0

#include <iostream>
#include <fstream>
#include <assert.h>
#include <armadillo>
#include <smartplus/Libraries/Phase/state_variables.hpp>
#include <smartplus/Libraries/Phase/state_variables_T.hpp>
#include <smartplus/parameter.hpp>
#include <smartplus/Libraries/Maths/rotation.hpp>

using namespace std;
using namespace arma;

namespace smart{

//=====Private methods for state_variables_T===================================

//=====Public methods for state_variables_T============================================

/*!
  \brief default constructor
*/

//-------------------------------------------------------------
state_variables_T::state_variables_T() : state_variables(), Wm(4), Wt(3), Wm_start(4), Wt_start(3), dSdE(6,6), dSdEt(6,6), dSdT(1,6), drdE(1,6), drdT(1,1)
//-------------------------------------------------------------
{
    Q = 0.;
    r = 0.;
    Wt = zeros(3);
    Wt_start = zeros(3);
    dSdE = zeros(6,6);
    dSdEt = zeros(6,6);
    dSdT = zeros(1,6);
    drdE = zeros(1,6);
    drdT = zeros(1,1);
}

/*!
  \brief Constructor with parameters
  \n\n
  \f$ \textbf{Examples :} \f$ \n
*/

//-------------------------------------------------------------
state_variables_T::state_variables_T(const vec &mEtot, const vec &mDEtot, const vec &msigma, const vec &msigma_start, const double &mT, const double &mDT, const int &mnstatev, const vec &mstatev, const vec &mstatev_start, const double &mQ, const double &mr, const vec &mWm, const vec &mWt, const vec &mWm_start, const vec &mWt_start, const mat &mdSdE, const mat &mdSdEt, const mat &mdSdT, const mat &mdrdE, const mat &mdrdT) : state_variables(mEtot, mDEtot, msigma, msigma_start, mT, mDT, mnstatev, mstatev, mstatev_start), Wm(4), Wt(3), Wm_start(4), Wt_start(3), dSdE(6,6), dSdEt(6,6), dSdT(1,6), drdE(1,6), drdT(1,1)
//-------------------------------------------------------------
{	

    assert (mWm.size() == 4);
    assert (mWt.size() == 3);
    
    assert (mWm_start.size() == 4);
    assert (mWt_start.size() == 3);
    
	assert (mdSdE.n_rows == 6);
	assert (mdSdE.n_cols == 6);

    assert (mdSdEt.n_rows == 6);
	assert (mdSdEt.n_cols == 6);
    
    assert (mdSdT.n_rows == 1);
    assert (mdSdT.n_cols == 6);
    
    assert (mdrdE.n_rows == 1);
    assert (mdrdE.n_cols == 6);
    
    assert (mdrdT.n_rows == 1);
    assert (mdrdT.n_cols == 1);

    Q = mQ;
    r = mr;
    Wm = mWm;
    Wm_start = mWm_start;
    Wt = mWt;
    Wt_start = mWt_start;
    dSdE = mdSdE;
	dSdEt = mdSdEt;
    dSdT = mdSdT;
    drdE = mdrdE;
    drdT = mdrdT;
}

/*!
  \brief Copy constructor
  \param s state_variables_T object to duplicate
*/

//------------------------------------------------------
state_variables_T::state_variables_T(const state_variables_T& sv) : state_variables(sv), Wm(4), Wt(3), Wm_start(4), Wt_start(3), dSdE(6,6), dSdEt(6,6), dSdT(1,6), drdE(1,6), drdT(1,1)
//------------------------------------------------------
{
    Q = sv.Q;
    r = sv.r;
    Wm = sv.Wm;
    Wt = sv.Wt;
    Wm_start = sv.Wm_start;
    Wt_start = sv.Wt_start;
    dSdE = sv.dSdE;
	dSdEt = sv.dSdEt;
    dSdT = sv.dSdT;
    drdE = sv.drdE;
    drdT = sv.drdT;
}

/*!
  \brief Destructor

  Deletes statev_variables, the vectors and matrix, and table statev if nstatev is not null.
*/

//-------------------------------------
state_variables_T::~state_variables_T()
//-------------------------------------
{

}

/*!
  \brief Standard operator = for state_variables
*/

//----------------------------------------------------------------------
state_variables_T& state_variables_T::operator = (const state_variables_T& sv)
//----------------------------------------------------------------------
{
    Etot = sv.Etot;
    DEtot = sv.DEtot;
    sigma = sv.sigma;
    sigma_start = sv.sigma_start;
    dSdE = sv.dSdE;
    dSdEt = sv.dSdEt;
    dSdT = sv.dSdT;
    drdE = sv.drdE;
    drdT = sv.drdT;
    Wm = sv.Wm;
    Wt = sv.Wt;
    Wm_start = sv.Wm_start;
    Wt_start = sv.Wt_start;
    
    Q = sv.Q;
    r = sv.r;
    T = sv.T;
    DT = sv.DT;

	return *this;
}

//-------------------------------------------------------------
void state_variables_T::update(const vec &mEtot, const vec &mDEtot, const vec &msigma, const vec &msigma_start, const double &mT, const double &mDT, const int &mnstatev, const vec &mstatev, const vec &mstatev_start, const double &mQ, const double &mr, const vec &mWm, const vec &mWt, const vec &mWm_start, const vec &mWt_start, const mat &mdSdE, const mat &mdSdEt, const mat &mdSdT, const mat &mdrdE, const mat &mdrdT)
//-------------------------------------------------------------
{
    state_variables::update(mEtot, mDEtot, msigma, msigma_start, mT, mDT, mnstatev, mstatev, mstatev_start);
    
    assert (mWm.size() == 4);
    assert (mWt.size() == 3);
    
    assert (mWm_start.size() == 4);
    assert (mWt_start.size() == 3);
    
    assert (mdSdE.n_rows == 6);
    assert (mdSdE.n_cols == 6);
    
    assert (mdSdEt.n_rows == 6);
    assert (mdSdEt.n_cols == 6);
    
    assert (mdSdT.n_rows == 1);
    assert (mdSdT.n_cols == 6);
    
    assert (mdrdE.n_rows == 1);
    assert (mdrdE.n_cols == 6);
    
    assert (mdrdT.n_rows == 1);
    assert (mdrdT.n_cols == 1);
    
    Q = mQ;
    r = mr;
    Wm = mWm;
    Wt = mWt;
    Wm_start = mWm_start;
    Wt_start = mWt_start;
    dSdE = mdSdE;
    dSdEt = mdSdEt;
    dSdT = mdSdT;
    drdE = mdrdE;
    drdT = mdrdT;
}
    
//-------------------------------------------------------------
void state_variables_T::to_start()
//-------------------------------------------------------------
{
    state_variables::to_start();
    Wm = Wm_start;
    Wt = Wt_start;
}

//-------------------------------------------------------------
void state_variables_T::set_start()
//-------------------------------------------------------------
{
    state_variables::set_start();
    Wm_start = Wm;
    Wt_start = Wt;
}
    
//----------------------------------------------------------------------
state_variables_T& state_variables_T::rotate_l2g(const state_variables_T& sv, const double &psi, const double &theta, const double &phi)
//----------------------------------------------------------------------
{

    state_variables::rotate_l2g(sv, psi, theta, phi);

    dSdE = sv.dSdE;
    dSdEt = sv.dSdEt;
    dSdT = sv.dSdT;
    drdE = sv.drdE;
    drdT = sv.drdT;
    Q = sv.Q;
    r = sv.r;
    Wm = sv.Wm;
    Wt = sv.Wt;
    Wm_start = sv.Wm_start;
    Wt_start = sv.Wt_start;
    
  	if(fabs(phi) > iota) {
		dSdE = rotateL(dSdE, -phi, axis_phi);
		dSdEt = rotateL(dSdEt, -phi, axis_phi);
        dSdT = rotate_stress(dSdT, -phi, axis_phi);
		drdE = rotate_strain(drdE, -phi, axis_phi);
	}
  	if(fabs(theta) > iota) {
		dSdE = rotateL(dSdE, -theta, axis_theta);
		dSdEt = rotateL(dSdEt, -theta, axis_theta);
        dSdT = rotate_stress(dSdT, -theta, axis_theta);
		drdE = rotate_strain(drdE, -theta, axis_theta);
	}
	if(fabs(psi) > iota) {
		dSdE = rotateL(dSdE, -psi, axis_psi);
		dSdEt = rotateL(dSdEt, -psi, axis_psi);
        dSdT = rotate_stress(dSdT, -psi, axis_psi);
		drdE = rotate_strain(drdE, -psi, axis_psi);
	}
    
	return *this;
}

//----------------------------------------------------------------------
state_variables_T& state_variables_T::rotate_g2l(const state_variables_T& sv, const double &psi, const double &theta, const double &phi)
//----------------------------------------------------------------------
{

    state_variables::rotate_g2l(sv, psi, theta, phi);
    
    dSdE = sv.dSdE;
    dSdEt = sv.dSdEt;
    dSdT = sv.dSdT;
    drdE = sv.drdE;
    drdT = sv.drdT;
    Q = sv.Q;
    r = sv.r;
    Wm = sv.Wm;
    Wt = sv.Wt;
    Wm_start = sv.Wm_start;
    Wt_start = sv.Wt_start;
    
  	if(fabs(psi) > iota) {
		dSdE = rotateL(dSdE, psi, axis_psi);
		dSdEt = rotateL(dSdEt, psi, axis_psi);
        dSdT = rotate_stress(dSdT, psi, axis_psi);
        drdE = rotate_strain(drdE, psi, axis_psi);
        
	}			
	if(fabs(theta) > iota) {
		dSdE = rotateL(dSdE, theta, axis_theta);
		dSdEt = rotateL(dSdEt, theta, axis_theta);
        dSdT = rotate_stress(dSdT, theta, axis_theta);
        drdE = rotate_strain(drdE, theta, axis_theta);
	}
	if(fabs(phi) > iota) {
		dSdE = rotateL(dSdE, phi, axis_phi);
		dSdEt = rotateL(dSdEt, phi, axis_phi);
        dSdT = rotate_stress(dSdT, phi, axis_phi);
        drdE = rotate_strain(drdE, phi, axis_phi);
    }
    
	return *this;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& s, const state_variables_T& sv)
//--------------------------------------------------------------------------
{
	s << "Etot: \n" << sv.Etot << "\n";
	s << "DEtot: \n" << sv.DEtot << "\n";
	s << "sigma: \n" << sv.sigma << "\n";
	s << "sigma_start: \n" << sv.sigma_start << "\n";
    s << "T: \n" << sv.T << "\n";
    s << "DT: \n" << sv.DT << "\n";
    s << "Q: \n" << sv.Q << "\n";
    s << "r: \n" << sv.r << "\n";
    s << "Wm: \n" << sv.Wm << "\n";
    s << "Wm_start: \n" << sv.Wm_start << "\n";
    s << "Wt: \n" << sv.Wt << "\n";
    s << "Wt_start: \n" << sv.Wt_start << "\n";
	s << "dSdE: \n" << sv.dSdE << "\n";
	s << "dSdEt: \n" << sv.dSdEt << "\n";
	s << "dSdT: \n" << sv.dSdT << "\n";
	s << "drdE: \n" << sv.drdE << "\n";
	s << "drdT: \n" << sv.drdT << "\n";
    
    s << "nstatev: \n" << sv.nstatev << "\n";
    if (sv.nstatev) {
        s << "statev: \n";
        s << sv.statev.t();
        s << "\n";
        s << sv.statev_start.t();
        s << "\n";
    }    
    
	s << "\n";

	return s;
}

} //namespace smart
