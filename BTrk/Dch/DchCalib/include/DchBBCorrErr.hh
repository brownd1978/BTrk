//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id: DchBBCorrErr.hh 88 2010-01-14 12:32:57Z stroili $
//
// Description:
//	Class DchBBCorrErr
//	Dch Transient class containing DchPID Bethe-Bloch parameters
//
// Environment:
//	Software developed for the BaBar Detector at the SLAC B-Factory.
//
// Author List:
//	F. Galeazzi		Originator
//
// Changes:
//      J. Roy     10-Jan-2000
//      Added a second sigma function with a different signature
//
// Copyright Information:
//	Copyright (C) 1999	INFN & University of Padova
//
//------------------------------------------------------------------------
#ifndef DCHBBCORRERR_HH
#define DCHBBCORRERR_HH

#include <vector>
#include <string>
#include "PDT/PdtPid.hh"
#include <iostream>
class TrkRecoTrk;

class DchBBCorrErr 
{
public:
  // Constructors
  DchBBCorrErr( const std::vector<double>& parVector,
                    const char* functionName );
  // Destructor
  virtual ~DchBBCorrErr( );

  const char* channelName( ) const { return _functionName.c_str(); }
  unsigned numberOfParameters( ) const { return _par.size(); }
  double fieldValue( unsigned i ) const { return _par[i]; }
  virtual double sigma( double dedx, int samples, double momentum=0, 
                        PdtPid::PidType hypo=PdtPid::pion ) const = 0;
  virtual double sigma( double dedx, int samples, double error,
                        const TrkRecoTrk* track,
                        PdtPid::PidType hypo=PdtPid::pion ) const = 0;
  void print( std::ostream& o) const;

private:
  std::vector<double> _par;
  std::string _functionName;
};

#endif // DCHBBCORRERR_HH