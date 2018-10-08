//  -------------------------------------------------------------------------
//  Copyright (C) 2016 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "ramses-framework-api/RamsesFrameworkConfig.h"
#include "RamsesFrameworkConfigImpl.h"

namespace ramses
{
    RamsesFrameworkConfig::RamsesFrameworkConfig(int32_t argc, char const* const* argv)
        : StatusObject(*new RamsesFrameworkConfigImpl(argc, argv))
        , impl(static_cast<RamsesFrameworkConfigImpl&>(StatusObject::impl))
    {
    }

    RamsesFrameworkConfig::RamsesFrameworkConfig(int32_t argc, char * argv[])
        : StatusObject(*new RamsesFrameworkConfigImpl(argc, const_cast<const char**>(argv)))
        , impl(static_cast<RamsesFrameworkConfigImpl&>(StatusObject::impl))
    {
    }

    RamsesFrameworkConfig::~RamsesFrameworkConfig()
    {
    }

    status_t RamsesFrameworkConfig::setRequestedRamsesShellType(ERamsesShellType requestedShellType)
    {
        const status_t status = impl.setRequestedRamsesShellType(requestedShellType);
        return status;
    }

    status_t RamsesFrameworkConfig::setWatchdogNotificationInterval(ERamsesThreadIdentifier thread, uint32_t interval)
    {
        return impl.setWatchdogNotificationInterval(thread, interval);
    }

    status_t RamsesFrameworkConfig::setWatchdogNotificationCallBack(IThreadWatchdogNotification* callback)
    {
        return impl.setWatchdogNotificationCallBack(callback);
    }

    void RamsesFrameworkConfig::setDLTApplicationID(const char* id)
    {
        impl.setDLTApplicationID(id);
    }

    const char* RamsesFrameworkConfig::getDLTApplicationID() const
    {
        return impl.getDLTApplicationID();
    }

    void RamsesFrameworkConfig::setDLTApplicationDescription(const char* description)
    {
        impl.setDLTApplicationDescription(description);
    }

    const char* RamsesFrameworkConfig::getDLTApplicationDescription() const
    {
        return impl.getDLTApplicationDescription();
    }

    void RamsesFrameworkConfig::setMaximumTotalBytesAllowedForAsyncResourceLoading(uint32_t maximumTotalBytesForAsynResourceLoading)
    {
        impl.setMaximumTotalBytesAllowedForAsyncResourceLoading(maximumTotalBytesForAsynResourceLoading);
    }

    void RamsesFrameworkConfig::setPeriodicLogsEnabled(bool enabled)
    {
        impl.setPeriodicLogsEnabled(enabled);
    }

    void RamsesFrameworkConfig::setInterfaceSelectionIPForTCPCommunication(const char* ip)
    {
        impl.m_tcpConfig.setIPAddress(ip);
    }

    void RamsesFrameworkConfig::setDaemonIPForTCPCommunication(const char* ip)
    {
        impl.m_tcpConfig.setDaemonIPAddress(ip);
    }

    void RamsesFrameworkConfig::setDaemonPortForTCPCommunication(uint16_t port)
    {
        impl.m_tcpConfig.setDaemonPort(port);
    }
}
