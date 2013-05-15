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


#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include "notificationparameters.h"
#include <QVariant>

class QDataStream;
class QDBusArgument;

/*!
 * \brief A class for storing notification information.
 *
 * The information can also be serialized in and out of a QDataStream.
 */
class Notification
{
public:
    /*!
     * Notification types.
     */
    enum NotificationType {
        ApplicationEvent,
        SystemEvent
    };

    /*!
     * Empty constructor. Initializes the values to defaults.
     */
    Notification();

    /*!
     * Constructor.
     *
     * \param notificationId the ID of this notification
     * \param groupId the group ID of this notification
     * \param userId the user ID associated to this notification
     * \param parameters parameters for the notification to be presented
     * \param type the type of the notification to be presented. \see NotificationType.
     * \param timeout The number of milliseconds to present the notification for
     */
    Notification(uint notificationId, uint groupId, uint userId, const NotificationParameters &parameters, NotificationType type, int timeout);

    /*!
     * Destructor.
     */
    ~Notification();

    /*!
     * Returns the ID of this notification.
     *
     * \return ID of this notification
     */
    uint notificationId() const;

    /*!
     * Returns the user ID associated with this notification.
     *
     * \return user ID associated with this notification
     */
    uint userId() const;

    /*!
     * Returns the group ID of this notification.
     *
     * \return group ID of this notification
     */
    uint groupId() const;

    /*!
     * Returns the parameters list for this notification.
     *
     * \return parameters list for this notification
     */
    const NotificationParameters &parameters() const;

    /*!
     * Sets the parameters list for this notification.
     *
     * \param parameters parameters for this notification
     * \sa updateParameters
     */
    void setParameters(const NotificationParameters &parameters);

    /*!
     * Updates the parameters of this notification. The existing parameters in the
     * notification remain as they are. Only new values from the argument are appended/updated.
     * \param parameters the parameters that will be updated
     * \sa setParameters
     */
    void updateParameters(const NotificationParameters &parameters);

    /*!
     * Returns the type of this notification.
     *
     * \return type of this notification
     */
    NotificationType type() const;

    /*!
     * Returns the timeout of this notification.
     *
     * \return timeout of this notification
     */
    int timeout() const;


    friend QDataStream &operator<<(QDataStream &, const Notification &);
    friend QDataStream &operator>>(QDataStream &, Notification &);

    friend QDBusArgument &operator<<(QDBusArgument &, const Notification &notification);
    friend const QDBusArgument &operator>>(const QDBusArgument &, Notification &);

private:
    //! The ID of the notification to be presented
    uint notificationId_;
    //! The ID of the notification group
    uint groupId_;
    //! The user ID associated with this notification
    uint userId_;
    //! The parameters for the notification to be presented
    NotificationParameters parameters_;
    //! The type of the notification to be presented
    NotificationType type_;
    //! The number of milliseconds to present the notification for
    int timeout_;
};

Q_DECLARE_METATYPE(Notification)

/*!
 * Serializes the given Notification to a QDataStream
 *
 * \param datastream QDataStream to write to
 * \param notification Notification object to serialize
 */
QDataStream &operator<<(QDataStream &datastream, const Notification &notification);

/*!
 * Deserializes a Notification from a QDataStream
 *
 * \param datastream QDataStream to read from
 * \param notification the target Notification object, its previous state will be reset
 */
QDataStream &operator>>(QDataStream &datastream, Notification &notification);


#endif // NOTIFICATION_H_
