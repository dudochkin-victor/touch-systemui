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

#ifndef NOTIFICATIONMANAGER_H_
#define NOTIFICATIONMANAGER_H_

#include "notification.h"
#include "notificationgroup.h"
#include "notificationmanagerinterface.h"
#include "eventtypestore.h"

#include <QObject>
#include <QHash>
#include <QSet>
#include <QTimer>
#include <QSharedPointer>
#include <QBuffer>

class ApplicationContext;
class DBusInterfaceNotificationSource;
class DBusInterfaceNotificationSink;

/*!
 * The NotificationManager allows a program to display a notification,
 * update the contents of a notification and cancel a notification.
 */
class NotificationManager : public QObject, public NotificationManagerInterface
{
    Q_OBJECT

public:
    /*!
     * Creates a new NotificationManager.
     * \param relayInterval Time interval in milliseconds between relaying submitted notifications from
     * this NotificationManager onwards to entities connected to notificationUpdated() signal. If this timeout
     * is zero this NotificationManager will pass through all notifications sent using displayNotification()
     * immediatelly. If this interval is negative the relay interval is infinite. Its then on the
     * responsibility of a derived class to call relayNextNotification() when next notification should be
     * relayed.
     * \param maxWaitQueueSize The maximum amount of notifications that can be store in this NotificationManager's
     * wait queue awaiting their turn to be relayed to entities connected to notificationUpdated(). Any
     * incoming notification sent through addNotification() when wait queue is full is dropped.
     */
    NotificationManager(int relayInterval = 3000, uint maxWaitQueueSize = 100);

    /*!
     * Destroys the NotificationManager.
     */
    virtual ~NotificationManager();


    /*!
     * Restores data.
     *
     * Restores the saved groups and notifications and sends the respective notificationUpdated and groupUpdated signals.
     */
    void restoreData();

    //! \reimp
    QList<Notification> notifications() const;
    QList<NotificationGroup> groups() const;
    virtual QObject *qObject();
    //! \reimp_end

public slots:
    //! \reimp
    uint addNotification(uint notificationUserId, const NotificationParameters &parameters = NotificationParameters(), uint groupId = 0);
    bool updateNotification(uint notificationUserId, uint notificationId, const NotificationParameters &parameters = NotificationParameters());
    bool removeNotification(uint notificationUserId, uint notificationId);
    uint addGroup(uint notificationUserId, const NotificationParameters &parameters = NotificationParameters());
    bool updateGroup(uint notificationUserId, uint groupId, const NotificationParameters &parameters = NotificationParameters());
    bool removeGroup(uint notificationUserId, uint groupId);
    uint notificationUserId();
    QList<uint> notificationIdList(uint notificationUserId);
    QList<Notification> notificationList(uint notificationUserId);
    QList<Notification> notificationListWithIdentifiers(uint notificationUserId);
    QList<NotificationGroup> notificationGroupList(uint notificationUserId);
    QList<NotificationGroup> notificationGroupListWithIdentifiers(uint notificationUserId);
    uint notificationCountInGroup(uint notificationUserId, uint groupId);
    //! \reimp_end

    /*!
     * Removes a notification. This slot is for the sinks so they can remove notifications without needing to know the notification user ID.
     *
     * \param notificationId The ID of the notification to be removed.
     * \return true if the removal succeeded, false otherwise
     */
    bool removeNotification(uint notificationId);

    /*!
     * Removes all notifications from a group. This slot is for the sinks so they can remove notifications without needing to know the notification user ID.
     *
     * \param groupId The ID of the group from which notifications should be removed.
     * \return true if the removal succeeded, false otherwise
     */
    bool removeNotificationsInGroup(uint groupId);

    /*!
     * Removes all notifications and groups with the specified event type
     * \param eventType the event type of the notifications and groups to remove
     */
    void removeNotificationsAndGroupsWithEventType(const QString &eventType);

    /*!
     * \brief Update event type data of all notifications with the specified event type
     *
     * Sends a notificationUpdated(Notification &) signal for all notifications of specified type
     * so that sinks can update the event type data from the event type store
     *
     * \param eventType the event type of the notifications to update
     */
    void updateNotificationsWithEventType(const QString &eventType);

signals:
    /*!
     * A signal for notifying that the contents of a notification
     * has changed. The notification can be a new notification or a
     * pre-existing notification.
     * \param notification the data of the notification
     */
    void notificationUpdated(const Notification &notification);

    /*!
     * A signal for notifying that a certain notification has been removed.
     * \param notificationId the ID of the notification to be removed
     */
    void notificationRemoved(uint notificationId);

    /*!
     * A signal for notifying that the contents of a notification group has changed.
     * The group can be a new group or a pre-existing group.
     * \param groupId The ID of the notification group
     * \param parameters NotificationParameters for the group
     */
    void groupUpdated(uint groupId, const NotificationParameters &parameters);

    /*!
     * A signal for notifying that a notification group has been removed.
     * \param groupId the ID of the notification group to be removed
     */
    void groupRemoved(uint groupId);

    /*!
     * A signal for notifying that a pre-existing notification has been
     * restored from the persistent storage.
     * \param notification the data of the notification
     */
    void notificationRestored(const Notification &notification);

    /*!
     * Signal used to queue group removal request
     * \param groupId to be removed
     */
    void queuedGroupRemove(uint groupId);

    /*!
     * Signal used to queue notification removal request
     * \param notificationId notificationId to be removed
     */
    void queuedNotificationRemove(uint notificationId);


protected slots:
    /*!
     * Slot called to relay next notification from the notifications queue of this
     * NotificationManager.
     * This slot is called automatically periodically with the given relay interval
     * if the relay interval is given in the constructor. If negative relay interval
     * was specified in the constructor of this NotificationManager then this slot
     * has to be called manually by an inherited NotificationManager.
     * Every call to this slot will relay the first notification in the notification
     * queue. This will initiate the sequence of emitting the addNotification() signal
     * of this object and invoke any entity connected to this NotificationManager.
     */
    void relayNextNotification();
    /*!
      * Slot for setting unseen flags of all notifications to false.
      * \param ignore  \c true if ignore the call \c false to remove the flags
      */
    void removeUnseenFlags(bool ignore);

private slots:
    /*!
     * Removes groups from internal storage
     * \param groupId groupId to be removed
     */
    void doRemoveGroup(uint groupId);

private:

    /*!
     * Determines the type of a notification from the notification parameters.
     *
     * \param parameters NotificationParameters to determine the type from
     * \return the type of the notification
     */
    Notification::NotificationType determineType(const NotificationParameters &parameters);

    /*!
     * Handles the notification which either signals addNotification() immediatelly
     * or adds the notification into the notification wait queue to be processed later.
     * \param notification The submitted notification object.
     */
    void submitNotification(const Notification &notification);

    /*!
     * Appends the notification parameters determined by the event type to the parameters
     * and returns a new instance of the complete parameters. The returned parameters contain
     * both the parameters supplied in the \a parameters argument as well as thos determined
     * by the event type configuration.
     * @param parameters the notification parameters.
     * @return the parameters passed in as an argument appended with the event type specific parameters.
     */
    NotificationParameters appendEventTypeParameters(const NotificationParameters &parameters) const;

    /*!
     * Returns the index of a notification in the wait queue matching the notification
     * id given as a parameter.
     * \param notificationId Notification ID to be searched from the wait queue.
     * \returns Index of matching notification in the wait queue or -1 if no matching
     * notification is found.
     */
    int findNotificationFromWaitQueue(uint notificationId);

    /*!
     * Returns the next available notification ID
     *
     * \return The next available notification ID
     */
    uint nextAvailableNotificationID();

    /*!
     * Returns the next available notification group ID
     *
     * \return The next available notification group ID
     */
    uint nextAvailableGroupID();

    /*!
     * Initializes the notification user ID data store.
     */
    void initializeNotificationUserIdDataStore();

    /*!
     * Initializes the event type store.
     */
    void initializeEventTypeStore();

    /*!
     * Ensures the persistent data directory exists
     *
     * \return false if the directory didn't exist and couldn't be created
     */
    bool ensurePersistentDataPath();

    /*!
     * Stores the group information and the last user id to a permanent storage
     */
    void saveStateData();

    /*!
     * Stores the notifications to a permanent storage
     */
    void saveNotifications();

    //! Hash of all notifications keyed by notification IDs
    QHash<uint, Notification> notificationContainer;

    //! Hash of all notification groups keyed by group IDs
    QHash<uint, NotificationGroup> groupContainer;

    //! Used to store notifications that wait their turn to be relayed to sinks.
    QList<Notification> waitQueue;

    //! Maximum amount of notifications in the wait queue.
    const uint maxWaitQueueSize;

    //! Timer to trigger new notifications from the wait queue
    QTimer waitQueueTimer;

    //! Indicator whether notification is currently being processed by sinks or not
    bool notificationInProgress;

    //! Time interval in milliseconds between sending notifications from this NotificationManager
    int relayInterval;

    //! Current application context to access various backends.
    ApplicationContext *context;

    //! DBus interface notification source
    DBusInterfaceNotificationSource *dBusSource;

    //! DBus interface notification sink
    DBusInterfaceNotificationSink *dBusSink;

    //! EventTypeStore for notification event types
    QSharedPointer<EventTypeStore> notificationEventTypeStore;

    //! The last used notification user ID
    quint32 lastUsedNotificationUserId;

    //! Flag to determine if the persistent data has been restored yet
    bool persistentDataRestored;

#ifdef UNIT_TEST
    friend class Ut_NotificationManager;
#endif
};

#endif /* NOTIFICATIONMANAGER_H_ */
