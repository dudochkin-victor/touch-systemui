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

#include <MApplication>
#include "ut_notificationparameter.h"
#include "notificationparameter.h"


void Ut_NotificationParameter::initTestCase()
{
}

void Ut_NotificationParameter::cleanupTestCase()
{
}

void Ut_NotificationParameter::init()
{
}

void Ut_NotificationParameter::cleanup()
{
}

void Ut_NotificationParameter::testCreation()
{
    QString name = "Test";
    QVariant value(5);
    NotificationParameter parameter(name, value);
    QCOMPARE(parameter.name(), name);
    QCOMPARE(parameter.value(), value);
}

QTEST_MAIN(Ut_NotificationParameter)
