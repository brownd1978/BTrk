#ifndef KinKal_LHelix_hh
#define KinKal_LHelix_hh
// class desribing the looping helix basis for the kinematic Kalman fit
// It provides geometric, kinematic, and algebraic representation of
// a particule executing a multi-loop helix in a constant magnetic field.
//
// Original Author David Brown (LBNL) 1/2020
//

#include "BTrk/KinKal/Types.hh"
#include "BTrk/KinKal/KTraj.hh"
#include "BTrk/KinKal/Context.hh"
#include <vector>
#include <string>

namespace KinKal {

  class LHelix : public KTraj<6> {
    public:
      // This struct must provide the following to be used to instantiate the 
      // classes implementing the Kalman fit
      // define the indices and names of the parameters
      enum paramIndex {rad_=0,lam_=1,cx_=2,cy_=3,phi0_=4,t0_=5,_npars=6};
      static size_t nParams() { return _npars; }
      static std::vector<std::string> const& paramNames(); 
      static std::vector<std::string> const& paramTitles();
      static std::string const& paramName(paramIndex index);
      static std::string const& paramTitle(paramIndex index);

      // construct from momentum, position, and particle properties
      LHelix(FourV const& pos, FourV const& mom, double charge, Context const& context);

      // particle position and momentum as a function of time
      void position(FourV& pos) const override; // time is input 
      void momentum(double t,FourV& mom) const override;

      // accessors
      double pbar() const { return  sqrt(pars_[rad_]*pars_[rad_] + pars_[lam_]*pars_[lam_] ); } // momentum in mm
      double ebar() const { return  sqrt(pars_[rad_]*pars_[rad_] + pars_[lam_]*pars_[lam_] + mbar_*mbar_); } // energy in mm
      // angular rotation frequency
      double omega() const { return copysign(c_,mbar_)/ebar(); } // rotational velocity, sign set by magnetic force 
      double beta() const { return pbar()/ebar(); }
      double phi(double t) const { return omega()*(t - pars_[t0_]) + pars_[phi0_]; }
      double time(double zpos) const { return pars_[t0_] + zpos/(omega()*pars_[lam_]); }

      // flip the helix in time; this also reverses the charge
      void reverse() {
	mbar_ *= -1.0;
	charge_ *= -1;
	pars_[t0_] *= -1.0;
      }
      //
    private :
      double mbar_;  // reduced mass in units of mm (computed from the mass);

      static std::vector<std::string> paramTitles_;
      static std::vector<std::string> paramNames_;
  };
}
#endif
