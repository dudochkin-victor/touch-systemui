/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of systemui.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QDBusArgument>
#include "notificationgroup.h"
#include "notificationwidgetparameterfactory.h"
#include "genericnotificationparameterfactory.h"

NotificationGroup::NotificationGroup() :
    groupId_(0),
    userId_(0),
    parameters_()
{
}

NotificationGroup::NotificationGroup(uint groupId, uint userId, const NotificationParameters &parameters) :
    groupId_(groupId),
    userId_(userId),
    parameters_(parameters)
{
}

NotificationGroup::~NotificationGroup()
{
}

uint NotificationGroup::groupId() const
{
    return groupId_;
}

uint NotificationGroup::userId() const
{
    return userId_;
}

const NotificationParameters &NotificationGroup::parameters() const
{
    return parameters_;
}

void NotificationGroup::setParameters(const NotificationParameters &parameters)
{
    parameters_ = parameters;
}

void NotificationGroup::updateParameters(const NotificationParameters &parameters)
{
    parameters_.update(parameters);
}


QDataStream &operator<<(QDataStream &datastream, const NotificationGroup &notificationGroup)
{
    datastream << notificationGroup.groupId_;
    datastream << notificationGroup.userId_;
    datastream << notificationGroup.parameters_;
    return datastream;
}

QDataStream &operator>>(QDataStream &datastream, NotificationGroup &notificationGroup)
{
    datastream >> notificationGroup.groupId_;
    datastream >> notificationGroup.userId_;
    datastream >> notificationGroup.parameters_;
    return datastream;
}

QDBusArgument &operator<<(QDBusArgument &argument, const NotificationGroup &group)
{
    argument.beginStructure();
    argument << group.groupId_;
    argument << group.userId_;
    argument << group.parameters_;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, NotificationGroup &group)
{
    argument.beginStructure();
    argument >> group.groupId_;
    argument >> group.userId_;
    argument >> group.parameters_;
    argument.endStructure();

    return argument;
}
