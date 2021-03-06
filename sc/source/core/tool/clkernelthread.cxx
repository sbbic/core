/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <sal/log.hxx>

#include "formulagroup.hxx"
#include "grouptokenconverter.hxx"

#include "clkernelthread.hxx"

using namespace std;

namespace sc {

CLBuildKernelThread::CLBuildKernelThread() :
    salhelper::Thread("opencl-build-kernel-thread")
{
}

CLBuildKernelThread::~CLBuildKernelThread()
{
}

void CLBuildKernelThread::execute()
{
    SAL_INFO("sc.opencl.thread", "running");

    bool done = false;
    while (!done)
    {
        SAL_INFO("sc.opencl.thread", "waiting for condition");
        maQueueCondition.wait();
        SAL_INFO("sc.opencl.thread", "got condition");
        osl::ResettableMutexGuard aGuard(maQueueMutex);
        maQueueCondition.reset();
        while (!maQueue.empty())
        {
            CLBuildKernelWorkItem aWorkItem = maQueue.front();
            maQueue.pop();
            aGuard.clear();

            switch (aWorkItem.meWhatToDo)
            {
            case CLBuildKernelWorkItem::COMPILE:
                SAL_INFO("sc.opencl.thread", "told to compile group " << aWorkItem.mxGroup << " (state " << aWorkItem.mxGroup->meCalcState << ") to binary");
                aWorkItem.mxGroup->compileOpenCLKernel();
                SAL_INFO("sc.opencl.thread", "group " << aWorkItem.mxGroup << " compilation done");
                maCompilationDoneCondition.set();
                break;
            case CLBuildKernelWorkItem::FINISH:
                SAL_INFO("sc.opencl.thread", "told to finish");
                done = true;
                break;
            }

            aGuard.reset();
        }
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
