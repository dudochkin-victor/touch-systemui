/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp notificationsink.xml -a notificationsinkadaptor -c NotificationSinkAdaptor -l NotificationSink -i notificationsink.h -i metatypedeclarations.h
 *
 * qdbusxml2cpp is Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "notificationsinkadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class NotificationSinkAdaptor
 */

NotificationSinkAdaptor::NotificationSinkAdaptor(NotificationSink *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

NotificationSinkAdaptor::~NotificationSinkAdaptor()
{
    // destructor
}

void NotificationSinkAdaptor::addGroup(uint groupId, NotificationParameters parameters)
{
    // handle method call com.meego.core.MNotificationSink.addGroup
    parent()->addGroup(groupId, parameters);
}

void NotificationSinkAdaptor::addNotification(Notification notification)
{
    // handle method call com.meego.core.MNotificationSink.addNotification
    parent()->addNotification(notification);
}

void NotificationSinkAdaptor::removeGroup(uint groupId)
{
    // handle method call com.meego.core.MNotificationSink.removeGroup
    parent()->removeGroup(groupId);
}

void NotificationSinkAdaptor::removeNotification(uint notificationId)
{
    // handle method call com.meego.core.MNotificationSink.removeNotification
    parent()->removeNotification(notificationId);
}

