//File:         JobDistributionModel.cpp
//Description:

#include "JobDistributionModel.hpp"

int JobDistributionModel::NextArrival = 0;
int JobDistributionModel::NextJobLength = 0;
int JobDistributionModel::NextVMSize = 0;
int JobDistributionModel::NextDataSize = 0;

JobArrivalDistributionFactory* JobDistributionModel::JobArrivalDistribution = NULL;
JobLengthDistributionFactory* JobDistributionModel::JobLengthDistribution = NULL;
JobVMSizeDistributionFactory* JobDistributionModel::JobVMSizeDistribution = NULL;
JobDataSizeDistributionFactory* JobDistributionModel::JobDataSizeDistribution = NULL;

void JobDistributionModel::Initialize()
{
  *_log.trace << "Initializing JobDistributionModel - Job Arrival" << std::endl;

  if (_configuration.JobArrival_Static)
  {
      JobArrivalDistribution = JobArrivalDistributionFactory::make_JobArrivalDistribution(Static);
	  JobArrivalDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobArrival_Poisson)
  {
    JobArrivalDistribution = JobArrivalDistributionFactory::make_JobArrivalDistribution(Poisson);
	JobArrivalDistribution->Initialize();
    *_log.trace << "   Poisson" << std::endl;
  }


  *_log.trace << "Initializing JobDistributionModel - Job Length" << std::endl;

  if (_configuration.JobLength_Static)
  {
      JobLengthDistribution = JobLengthDistributionFactory::make_JobLengthDistribution(Static);
	  JobLengthDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobLength_Normal)
  {
    JobLengthDistribution = JobLengthDistributionFactory::make_JobLengthDistribution(Normal);
	JobLengthDistribution->Initialize();
    *_log.trace << "   Normal" << std::endl;
  }


  *_log.trace << "Initializing JobDistributionModel - VM Size" << std::endl;

  if (_configuration.JobVMSize_Static)
  {
      JobVMSizeDistribution = JobVMSizeDistributionFactory::make_JobVMSizeDistribution(Static);
	  JobVMSizeDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobVMSize_Normal)
  {
    JobVMSizeDistribution = JobVMSizeDistributionFactory::make_JobVMSizeDistribution(Normal);
	JobVMSizeDistribution->Initialize();
    *_log.trace << "   Normal" << std::endl;
  }


  *_log.trace << "Initializing JobDistributionModel - Data Size" << std::endl;

  if (_configuration.JobDataSize_Static)
  {
      JobDataSizeDistribution = JobDataSizeDistributionFactory::make_JobDataSizeDistribution(Static);
	  JobDataSizeDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobDataSize_Normal)
  {
    JobDataSizeDistribution = JobDataSizeDistributionFactory::make_JobDataSizeDistribution(Normal);
	JobDataSizeDistribution->Initialize();
    *_log.trace << "   Normal" << std::endl;
  }
}


int JobDistributionModel::getNextArrival()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextArrival;
}


int JobDistributionModel::getNextVMSize()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextVMSize;
}


int JobDistributionModel::getNextDataSize()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextDataSize;
}


int JobDistributionModel::getNextJobLength()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextJobLength;
}


void JobDistributionModel::generateNext()
{
  *_log.trace << "JobDistributionModel.generateNext()" << std::endl;
  int offset = JobArrivalDistribution->getNext();
  NextArrival = NextArrival + offset;
  NextJobLength = JobLengthDistribution->getNext();
  NextVMSize = JobVMSizeDistribution->getNext();
  NextDataSize = JobDataSizeDistribution->getNext();
}
