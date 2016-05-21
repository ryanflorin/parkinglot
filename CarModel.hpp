//File:         CarModel.hpp
//Description:

#ifndef __CARMODEL_HPP__
#define __CARMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"
#include "CarResidencyDistributionModel.hpp"
#include "Job.hpp"
#include "JobModel.hpp"

#include <map>
#include <list>

class CarModel
{
  private:
    Logger _log;
	Configuration _configuration;
    TimeModel _time;
	CarResidencyDistributionModel _carResidencyDistributionModel;

    //carmap is indexed by parking spot number
	static std::map<int, Car*> carmap;
    static std::list<int> emptySpaces;

	//This is used to override some parts of CreateNewCar during the initialize phase.
	static bool initializing;


	void createNewCar();
	Car * GetMigrationToVehicle(Car* FromCar);
	void handleVehicleDepartingNOW();
	void handleVehicleDepartingSOON();
    void HandleDepartingVehicles();
	void HandleIncomingVehicles();

  public:
    void Initialize();

	Car* AssignJob(Job* job);
	std::list<Car*> AssignDataMigrationCars(Job* job);

	void PrintVehicleInfo();
	int getClusterNumber(int);
	int getRegionNumber(int);
	int getGroupNumber(int);

	void HandleCars();
};

#endif
