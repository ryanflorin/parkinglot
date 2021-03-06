//File:         JobVMSizeDistributionFactory.cpp
//Description:
#include <random>
#include "../Configuration.hpp"
#include "JobVMSizeDistributionFactory.hpp"

class NormalJobVMSize: public JobVMSizeDistributionFactory
{
	private:
        static std::default_random_engine generatorJobVMSize;
        static std::normal_distribution<double> * JobVMSizeNormalDistribution;


	public:
		void Initialize();
		int getNext();

};

std::default_random_engine NormalJobVMSize::generatorJobVMSize;
std::normal_distribution<double> * NormalJobVMSize::JobVMSizeNormalDistribution;

void NormalJobVMSize::Initialize()
{
	Configuration _configuration;
    generatorJobVMSize = std::default_random_engine(_configuration.Seed);
	JobVMSizeNormalDistribution = new std::normal_distribution<double>(_configuration.JobVMSize_Normal_Mean, _configuration.JobVMSize_Normal_STDev);
}

int NormalJobVMSize::getNext()
{
	return (*JobVMSizeNormalDistribution)(generatorJobVMSize);
}


class StaticJobVMSize: public JobVMSizeDistributionFactory
{
	private:
	    int staticValue;
	public:
		void Initialize();
		int getNext();

};

void StaticJobVMSize::Initialize()
{
	Configuration _configuration;
	staticValue = _configuration.JobVMSize_Static_Value;
}

int StaticJobVMSize::getNext()
{
	return staticValue;
}

JobVMSizeDistributionFactory *JobVMSizeDistributionFactory::make_JobVMSizeDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticJobVMSize;
	if (distribution == Normal)
		return new NormalJobVMSize;

    //Default to Static
    return new StaticJobVMSize;
}
