#include "vocale.h"
#include <QDebug>
#include <QDir>

Vocale::Vocale(QObject *parent) : QObject(parent), process(nullptr) {}

Vocale::~Vocale() {
}
void Vocale::startAudioCapture()
{
    qDebug() << "Current working directory: " << QDir::currentPath();
    QDir::setCurrent("C:/Users/DELL/Desktop/employe/speech_to_text.py");
    QProcess testPython;
    testPython.start("python", QStringList() << "--version");
    if (!testPython.waitForFinished()) {
        qDebug() << "Python is not accessible in this environment.";
    } else {
        qDebug() << "Python version: " << testPython.readAllStandardOutput();
    }

    if (process) {
        qDebug() << "Un processus est déjà en cours.";
        return;
    }

    qDebug() << "Starting audio capture...";

    process = new QProcess(this);
    if (!process->waitForStarted()) {
        qDebug() << "Failed to start the process. Error:" << process->errorString();
    }

    QString pythonExecutable = "python";
    QString scriptPath = "C:/Users/DELL/Desktop/employe/speech_to_text.py";
    if (!QFile::exists(scriptPath)) {
        qDebug() << "Le script Python n'existe pas au chemin : " << scriptPath;
        return;
    }

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start the process. Error:" << process->errorString();
    }

    qDebug() << "Script path: " << scriptPath;

    connect(process, &QProcess::readyReadStandardOutput, [this]() {
        QString output = process->readAllStandardOutput().trimmed();


        QStringList lines = output.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            if (line.contains("Recognized text:")) {
                QString recognizedText = line.mid(QString("Recognized text:").length()).trimmed();
                emit textCaptured(recognizedText);
            }
        }
    });


    connect(process, &QProcess::readyReadStandardError, [this]() {
        QString error = process->readAllStandardError().trimmed();
        qDebug() << "Process error: " << error;
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [this](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "Python process finished with exit code: " << exitCode << " and exit status: " << exitStatus;
    });

    qDebug() << "Starting process...";
    process->start(pythonExecutable, QStringList() << scriptPath);
    if (!process->waitForStarted()) {
        qDebug() << "Failed to start the process.";
    }
}

void Vocale::stopAudioCapture()
{
    if (process) {
        process->terminate();
        process->deleteLater();
        process = nullptr;
        qDebug() << "Process stopped.";
    }
}
