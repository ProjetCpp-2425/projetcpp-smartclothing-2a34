#ifndef VOCALE_H
#define VOCALE_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QDebug>

class Vocale : public QObject
{
    Q_OBJECT

public:
    explicit Vocale(QObject *parent = nullptr);
    ~Vocale();

    void startCapture();
    void stopCapture();

signals:
    void textCaptured(const QString &text);

private:
    QProcess *process;
    bool isCapturing;
    void handleOutput();
};

#endif // VOCALE_H
