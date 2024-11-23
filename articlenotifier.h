#ifndef ARTICLENOTIFIER_H
#define ARTICLENOTIFIER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QString>
#include <QDate>

class ArticleNotifier : public QObject {
    Q_OBJECT
public:
    ArticleNotifier();
    void notifyStockLow();
    void notifyPromotion();
    void notifyAnniversary();

private:
    QSystemTrayIcon trayIcon;
};

#endif // ARTICLENOTIFIER_H
