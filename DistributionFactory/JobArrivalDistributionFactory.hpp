//File:         JobArrivalDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_JobArrivalDistribution - returns a pointer to a Arrival Distribution
//      choice:0 - Static Arrival
//      choice:1 - Poisson Arrival


#ifndef __JOBARRIVALDISTRIBUTIONFACTORY_HPP__
#define __JOBARRIVALDISTRIBUTIONFACTORY_HPP__

#include "DistributionType.enum"

class JobArrivalDistributionFactory
{
	public:
	    static JobArrivalDistributionFactory *make_JobArrivalDistribution(DistributionType distribution);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual double getNext() = 0;      //=0 because we have to declare some function;

};

#endif
