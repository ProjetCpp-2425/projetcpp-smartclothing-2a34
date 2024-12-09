#ifndef VOCALE_H
#define VOCALE_H

#include <QObject>
#include <QString>
#include <QProcess>

class Vocale : public QObject
{
    Q_OBJECT

public:
    explicit Vocale(QObject *parent = nullptr);
    ~Vocale();

    void startAudioCapture(); // Démarre l'enregistrement vocal
    void stopAudioCapture();  // Stoppe l'enregistrement vocal

signals:
    void textCaptured(QString text); // Signal pour transmettre le texte capturé

private:
    QProcess *process; // Gère le processus Python

};

#endif // VOCALE_H
