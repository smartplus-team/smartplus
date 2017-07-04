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

///@file elastic_transversely_isotropic.cpp
///@brief User subroutine for transversely isotropic elastic materials in 3D case
///@version 1.0

#include <iostream>
#include <fstream>
#include <armadillo>
#include <smartplus/parameter.hpp>
#include <smartplus/Libraries/Continuum_Mechanics/constitutive.hpp>

using namespace std;
using namespace arma;

namespace smart {

///@brief The elastic istropic transverse UMAT requires 8 constants:
///@brief props[0] : Axe of the longitudinal direction
///@brief props[1] : Longitudinal Young modulus
///@brief props[2] : Transverse Young modulus
///@brief props[3] : Longitudinal-Transverse Poisson ratio
///@brief props[4] : Transverse-Transverse Poisson ratio
///@brief props[5] : Shear Modulus
///@brief props[6] : Longitudinal thermal expansion coeficient
///@brief props[7] : Transverse thermal expansion coeficient

///@brief No statev is required for thermoelastic constitutive law

void umat_elasticity_trans_iso(const vec &Etot, const vec &DEtot, vec &sigma, mat &Lt, const mat &DR, const int &nprops, const vec &props, const int &nstatev, vec &statev, const double &T, const double &DT, const double &Time, const double &DTime, double &Wm, double &Wm_r, double &Wm_ir, double &Wm_d, const int &ndi, const int &nshr, const bool &start, double &tnew_dt)
{  	

    UNUSED(Etot);
    UNUSED(DR);
    UNUSED(nprops);
    UNUSED(nstatev);
    UNUSED(statev);
    UNUSED(T);
    UNUSED(Time);
    UNUSED(DTime);
    UNUSED(nshr);
    UNUSED(tnew_dt);    
    
	//From the props to the material properties
	double axis = props(0);
	double EL = props(1);
	double ET = props(2);
	double nuTL = props(3);
	double nuTT = props(4);
	double GLT = props(5);
	double alphaL = props(6);
	double alphaT = props(7);
	
	// ######################  Elastic stiffness #################################			
	//defines L
	Lt = L_isotrans(EL, ET, nuTL, nuTT, GLT, axis);
	
	if(start) { //Initialization
		sigma = zeros(6);
	}	
	vec sigma_start = sigma;

	//definition of the CTE tensor
	vec alpha = zeros(6);
	alpha = alphaT*Ith();
	alpha(axis-1) += alphaL-alphaT;
	
	///Elastic prediction - Accounting for the thermal prediction

	//Compute the elastic strain and the related stress	
    vec Eel = Etot + DEtot - alpha*(T+DT-T_init);
    sigma = el_pred(Lt, Eel, ndi);
    
    //Computation of the mechanical and thermal work quantities
    Wm += 0.5*sum((sigma_start+sigma)%DEtot);
    Wm_r += 0.5*sum((sigma_start+sigma)%DEtot);
    Wm_ir += 0.;
    Wm_d += 0.;
}
    
} //namespace smart
