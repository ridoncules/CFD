#include "Parameters.hpp"

#include <stddef.h>
#include <algorithm>

#include "Constants.hpp"
#include "Converter.hpp"

void TorchParameters::initialise(std::shared_ptr<Constants>& consts) {
	tmax = consts->converter.toCodeUnits(tmax, 0, 0, 1);
	dt_max = tmax/10.0;
	sideLength = consts->converter.toCodeUnits(sideLength, 0, 1, 0);
	if (geometry.compare("spherical") == 0 || geometry.compare("cylindrical") == 0)
		leftBC[0] = "reflecting";
	photoIonCrossSection = consts->converter.toCodeUnits(photoIonCrossSection, 0, 2, 0); // P.I. cross-sect (cm^2/scale).
	alphaB = consts->converter.toCodeUnits(alphaB, 0, 3, -1); // Case B radiative recombination rate (cm^3 t^-1/scale).
	dfloor = consts->converter.toCodeUnits(dfloor, 1, -3, 0);
	pfloor =  0.1*consts->specificGasConstant*dfloor*tfloor;
	photonEnergy = consts->converter.toCodeUnits(photonEnergy, 1, 2, -2); // Source photon energy (erg/scale).
	photonRate = consts->converter.toCodeUnits(photonRate, 0, 0, -1); // Source photon Luminosity (s^-1/scale).
	massLossRate = consts->converter.toCodeUnits(massLossRate, 1, 0, -1); // Wind mass loss rate (g.s-1/scale).
	windVelocity = consts->converter.toCodeUnits(windVelocity, 0, 1, -1); // Wind velocity (cm.s-1/scale).

	const size_t len = outputDirectory.size();
	if ( outputDirectory[len-1] == '\\' || outputDirectory[len-1] == '/' )
		outputDirectory.pop_back();
}

GridParameters TorchParameters::getGridParameters() {
	GridParameters gpar;
	gpar.geometry = geometry;
	std::copy(std::begin(leftBC), std::end(leftBC), std::begin(gpar.leftBC));
	std::copy(std::begin(rightBC), std::end(rightBC), std::begin(gpar.rightBC));

	gpar.ncells = ncells;
	gpar.sideLength = sideLength;
	gpar.spatialOrder = spatialOrder;
	return gpar;
}

FluidParameters TorchParameters::getFluidParameters() {
	FluidParameters fpar;
	fpar.heatCapacityRatio = heatCapacityRatio;
	fpar.massFractionH = massFractionH;
	return fpar;
}

RadiationParameters TorchParameters::getRadiationParameters() {
	RadiationParameters rpar;
	rpar.K1 = K1;
	rpar.K2 = K2;
	rpar.K3 = K3;
	rpar.K4 = K4;
	rpar.THI = THI;
	rpar.THII = THII;
	rpar.tau0 = tau0;
	rpar.alphaB = alphaB;
	rpar.collisions_on = collisions_on;
	rpar.coupling = rt_coupling;
	rpar.heatingAmplification = heatingAmplification;
	rpar.scheme = rt_scheme;
	rpar.photoIonCrossSection = photoIonCrossSection;
	rpar.massFractionH = massFractionH;

	return rpar;
}

ThermoParameters TorchParameters::getThermoParameters() {
	ThermoParameters tpar;
	tpar.thermoHII_Switch = thermoHII_Switch;
	tpar.heatingAmplification = heatingAmplification;
	tpar.massFractionH = massFractionH;
	tpar.thermoSubcycling = thermoSubcycling;
	tpar.minTempInitialState = minTempInitialState;

	return tpar;
}

StarParameters TorchParameters::getStarParameters() {
	StarParameters spar;
	std::copy(faceSnap.begin(), faceSnap.end(), spar.faceSnap.begin());
	std::copy(star_position.begin(), star_position.end(), spar.position.begin());

	spar.on = star_on;
	if (star_on) {
		spar.massLossRate = massLossRate;
		spar.photonEnergy = photonEnergy;
		spar.photonRate = photonRate;
		spar.windCellRadius = windCellRadius;
		spar.windTemperature = windTemperature;
		spar.windVelocity = windVelocity;
	}

	return spar;
}
