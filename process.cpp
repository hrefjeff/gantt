/****************************************************
    Names       : Jeffrey Allen
    Date        : CS420 Spring 2014
    Assignment  : Assignment 11, Group 3
    Description : 
    Due Date: November 20, 2012
*****************************************************/

#include "process.h"
using namespace std;

Process::Process()
{
    name = "";
    number = 0;
    burstTime = 0;
    priority = 0;
    waitTime = 0;
    turnAroundTime = 0;
}

Process::Process(std::string newName, int pNum, int bTime, int plvl)
{
    name = newName;
    number = pNum;
    burstTime = bTime;
    priority = plvl;
    waitTime = 0;
    turnAroundTime = 0;
    startTime = 0;
    stopTime = 0;
}

Process::Process(Process * someProcess)
{
    name = someProcess->name;
    number = someProcess->number;
    burstTime = someProcess->burstTime;
    priority = someProcess->priority;
    waitTime = someProcess->waitTime;
    turnAroundTime = someProcess->turnAroundTime;
    startTime = someProcess->startTime;
    stopTime = someProcess->stopTime;
}

Process::~Process()
{
    name = "";
    number = 0;
    burstTime = 0;
    priority = 0;
    waitTime = 0;
    turnAroundTime = 0;
    startTime = 0;
    stopTime = 0;
}

std::string Process::getName()
{
    return name;
}

int Process::getNumber()
{
    return number;
}

int Process::getPriority()
{
    return priority;
}

int Process::getBurstTime()
{
    return burstTime;
}

int Process::getWaitTime()
{
    return waitTime;
}

int Process::getTurnAroundTime()
{
    return turnAroundTime;
}

int Process::getStartTime()
{
    return startTime;
}

int Process::getStopTime()
{
    return waitTime;
}

void Process::setName(std::string newName)
{
    name = newName;
}

void Process::setNumber(int newNumber)
{
    number = newNumber;
}

void Process::setPriority(int newPriority)
{
    priority = newPriority;
}

void Process::setBurstTime(int newBurstTime)
{
    burstTime = newBurstTime;
}

void Process::setWaitTime(int newWtime)
{
    waitTime = newWtime;
}

void Process::setTurnAroundTime(int newTtime)
{
    turnAroundTime = newTtime;
}

void Process::setStopTime(int stop)
{
    stopTime = stop;
}

void Process::setStartTime(int start)
{
    startTime = start;
}