/** Provides the Hydrodynamics class.
 * @file Hydro.hpp
 *
 * @author Harrison Steggles
 */

#ifndef HYDRO_HPP_
#define HYDRO_HPP_

#include <memory>

#include "Torch/Common.hpp"
#include "Integrator.hpp"
#include "Riemann.hpp"
#include "SlopeLimiter.hpp"

class Fluid;
class HydroParameters;
class Constants;

/**
 * @class HydroDynamics
 *
 * @brief Contains parameters and methods for hydrodynamic integration of a Fluid.
 *
 * @see Fluid
 * @see RiemannSolver
 * @see SlopeLimiter
 * @see Integrator
 */
class Hydrodynamics : public Integrator {

public:
	Hydrodynamics();
	~Hydrodynamics() {}

	void initialise(std::shared_ptr<Constants> c);

	virtual void preTimeStepCalculations(Fluid& fluid) const;
	virtual double calculateTimeStep(double dt_max, Fluid& fluid) const;
	virtual void integrate(double dt, Fluid& fluid) const;
	virtual void updateSourceTerms(double dt, Fluid& fluid) const;

	void setRiemannSolver(std::unique_ptr<RiemannSolver> riemannSolver);
	void setSlopeLimiter(std::unique_ptr<SlopeLimiter> slopeLimiter);

	// Calculation methods.
	void piecewiseLinear(FluidArray& Q_l, FluidArray& Q_c, FluidArray& Q_r, FluidArray& left_interp, FluidArray& right_interp) const;
	void reconstruct(Fluid& fluid) const;

	void calcFluxes(Fluid& fluid) const;
	void fixIC(Fluid& fluid) const;

private:
	std::shared_ptr<Constants> m_consts = nullptr;
	std::unique_ptr<RiemannSolver> m_riemannSolver = nullptr;
	std::unique_ptr<SlopeLimiter> m_slopeLimiter = nullptr;

	// Calculation methods.
	double soundSpeedSqrd(const double pre, const double den, const double gamma) const;
	double soundSpeed(const double pre, const double den, const double gamma) const;

	// Misc. methods.
	void Qisnan(const int id, const int i, const int xc, const int yc, const int zc) const;
};

#endif // HYDRO_HPP_
