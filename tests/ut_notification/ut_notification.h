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

#ifndef UT_NOTIFICATION_H
#define UT_NOTIFICATION_H

#include <QtTest/QtTest>
#include <QObject>


class Ut_Notification: public QObject
{
    Q_OBJECT

private slots:
    // Called before the first testfunction is executed
    void initTestCase();
    // Called after the last testfunction was executed
    void cleanupTestCase();
    // Called before each testfunction is executed
    void init();
    // Called after every testfunction
    void cleanup();

    void testWhenUpdatingNotificationParametersToNotificationThenTheParametersGetUpdated();
    void testWhenUpdatingNotificationParametersToNotificationThenTheOldParametersRemain();

    // Test serialization into QDataStream
    void testSerializationAndDeserialization();

    // Test serialization into QDBusArgument
    void testDBusSerialization();
};

#endif
