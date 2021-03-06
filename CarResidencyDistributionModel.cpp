//File:         CarResidencyDistributionModel.cpp
//Description: 	Provides random values for the car residency

#include "CarResidencyDistributionModel.hpp"

double CarResidencyDistributionModel::NextArrival = 0;
double CarResidencyDistributionModel::NextDeparture = 0;
CarArrivalDistributionFactory* CarResidencyDistributionModel::CarArrivalDistribution = NULL;
CarDepartureDistributionFactory* CarResidencyDistributionModel::CarDepartureDistribution = NULL;


void CarResidencyDistributionModel::Initialize()
{
  *_log.trace << "Initializing CarResidencyDistributionModel - Car Arrival" << std::endl;

  if (_configuration.CarArrival_FromFile)
  {
	  //Use pre-existing file
	  *_log.trace << "   From File" << std::endl;

  }
  else if (_configuration.CarArrival_Static)
  {
	  //CarResidency_Static_Hours;
      CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(Static);
	  CarArrivalDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarArrival_Poisson)
  {
    CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(Poisson);
	CarArrivalDistribution->Initialize();
    *_log.trace << "   Poisson" << std::endl;
  }

  *_log.trace << "Initializing CarResidencyDistributionModel - Car Departure" << std::endl;


  if (_configuration.CarDeparture_Static)
  {
	  //CarResidency_Static_Hours;
      CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(Static);
	  CarDepartureDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarDeparture_Exponential)
  {
    CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(Exponential);
	CarDepartureDistribution->Initialize();
    *_log.trace << "   Exponential" << std::endl;
  }
}


double CarResidencyDistributionModel::getNextArrival()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextArrival;
}


double CarResidencyDistributionModel::getNextDeparture()
{
	if (NextDeparture == 0)
	{
		generateNext();
	}
	return NextDeparture;
}


void CarResidencyDistributionModel::generateNext()
{
  *_log.trace << "CarResidencyDistributionModel.generateNext()" << std::endl;

  double baseTime = 0;
  if (_time.getTime() > 0)
  {
      baseTime = NextArrival;
  }

  double arrivalOffset = CarArrivalDistribution->getNext();
  double departureOffset = CarDepartureDistribution->getNext();

  NextArrival = baseTime + arrivalOffset;
  NextDeparture = NextArrival + departureOffset;
}

