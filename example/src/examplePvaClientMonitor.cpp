/*examplePvaClientClientMonitor.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 */

/* Author: Marty Kraimer */

#include <epicsThread.h>

#include <iostream>

#include <pv/pvaClient.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;


static void exampleMonitor(PvaClientPtr const &pva)
{
    PvaClientMonitorPtr monitor = pva->channel("examplePowerSupply")->monitor("");
    PvaClientMonitorDataPtr pvaData = monitor->getData();
    while(true) {
         monitor->waitEvent();
         cout << "changed\n";
         pvaData->showChanged(cout);
         cout << "overrun\n";
         pvaData->showOverrun(cout);
         monitor->releaseEvent();
     }
}


int main(int argc,char *argv[])
{
    PvaClientPtr pva = PvaClient::create();
    exampleMonitor(pva);
    cout << "done\n";
    return 0;
}