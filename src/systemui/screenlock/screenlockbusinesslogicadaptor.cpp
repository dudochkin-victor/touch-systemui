/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp screenlockbusinesslogic.xml -a screenlockbusinesslogicadaptor -c ScreenLockBusinessLogicAdaptor -l ScreenLockBusinessLogic -i screenlockbusinesslogic.h -i metatypedeclarations.h
 *
 * qdbusxml2cpp is Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "screenlockbusinesslogicadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class ScreenLockBusinessLogicAdaptor
 */

ScreenLockBusinessLogicAdaptor::ScreenLockBusinessLogicAdaptor(ScreenLockBusinessLogic *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

ScreenLockBusinessLogicAdaptor::~ScreenLockBusinessLogicAdaptor()
{
    // destructor
}

int ScreenLockBusinessLogicAdaptor::tklock_close(bool silent)
{
    // handle method call com.nokia.system_ui.request.tklock_close
    return parent()->tklock_close(silent);
}

int ScreenLockBusinessLogicAdaptor::tklock_open(const QString &service, const QString &path, const QString &interface, const QString &method, uint mode, bool silent, bool flicker)
{
    // handle method call com.nokia.system_ui.request.tklock_open
    return parent()->tklock_open(service, path, interface, method, mode, silent, flicker);
}

