//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id: DifIndepPar.hh 501 2010-01-14 12:46:50Z stroili $
//
// Description:
//	Class Header for |DifIndepPar|
//      Container class for a set of independ parameters
//
// Environment:
//	Software developed for the BaBar Detector at the SLAC B-Factory.
//
// Author List:
//	A. Snyder
//
// Copyright Information:
//	Copyright (C) 1996	SLAC
//
//------------------------------------------------------------------------

#ifndef DifIndepPar_HH
#define DifIndepPar_HH

#include "BTrk/BaBar/BaBar.hh"
#include <assert.h>
#include <stdlib.h>

#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Vector.h"

#include <iosfwd>
class DifArray;
class DifNumber;

class DifIndepPar {

public:

  DifIndepPar(int n);		// create slots for n parameters
  DifIndepPar(const CLHEP::HepVector& a);// from a vector of doubles
  DifIndepPar(const CLHEP::HepVector& pvec, const CLHEP::HepSymMatrix& pcov);// from a vector and an error matrix
  DifIndepPar(const DifIndepPar& rhs);// new set via copy of existing set

  DifArray difParameters()const; // return (by copy) array of indep parameters
  DifNumber difPar(int i)const; // fetch parameter i

  CLHEP::HepVector& parameter() { return parvec;}
  const CLHEP::HepVector& parameter() const { return parvec;}
  CLHEP::HepSymMatrix& covariance() { return parcov;}
  const CLHEP::HepSymMatrix& covariance() const { return parcov;}
  int nPar()const {return parvec.num_row();}

  //io
  void print(std::ostream& os = std::cout) const;
  void printAll(std::ostream& os = std::cout) const;

protected:
  //data
  CLHEP::HepVector parvec;                 //  Vector of parameters
  CLHEP::HepSymMatrix parcov;                 //  Covariance matrix on the parameters

  //private functions
  //  void setDerives();		// make numbers point at this

};

//io
inline std::ostream& operator<<(std::ostream& o,const DifIndepPar& i){ i.print(o); return o; }

#endif
