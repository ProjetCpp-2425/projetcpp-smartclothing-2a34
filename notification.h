#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QString>
#include <QDateTime>

class Notification {
public:
    QString message;   // Message de la notification
    QDateTime dateReceived;   // Date de réception de la notification
    bool isSeen;   // Statut si la notification a été vue ou non

    Notification(const QString &msg)
        : message(msg), dateReceived(QDateTime::currentDateTime()), isSeen(false) {}
};

#endif // NOTIFICATION_H
