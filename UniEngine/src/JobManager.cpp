#include "pch.h"
#include "JobManager.h"
using namespace UniEngine;


void JobManager::ResizePrimaryWorkers(int size)
{
	GetInstance().m_primaryWorkers.FinishAll(true);
	GetInstance().m_primaryWorkers.Resize(size);
}

void JobManager::ResizeSecondaryWorkers(int size)
{
	GetInstance().m_secondaryWorkers.FinishAll(true);
	GetInstance().m_secondaryWorkers.Resize(size);
}

ThreadPool& JobManager::PrimaryWorkers()
{
	return GetInstance().m_primaryWorkers;
}

ThreadPool& JobManager::SecondaryWorkers()
{
	return GetInstance().m_secondaryWorkers;
}