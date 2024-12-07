#include "Vocale.h"
#include <QProcess>
#include <QStringList>
#include <QDebug>

Vocale::Vocale(QObject *parent) : QObject(parent), process(nullptr), isCapturing(false)
{
}

Vocale::~Vocale()
{
    // Clean up
    if (process && process->state() == QProcess::Running) {
        process->terminate();
        process->waitForFinished();
    }
}

void Vocale::startCapture()
{
    if (isCapturing) {
        qDebug() << "Capture is already running.";
        return;
    }

    // Initialize the QProcess
    process = new QProcess(this);

    // Set the working directory (adjust if needed)
    process->setWorkingDirectory("C:/Users/DELL/Desktop/employe");

    // Set up the Python script path and arguments
    QStringList arguments;
    arguments << "C:/Users/DELL/Desktop/employe/speech_to_text.py";

    // Start the process
    process->start("python", arguments);

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start the process.";
        return;
    }

    qDebug() << "Process started successfully.";

    // Connect the process' readyReadStandardOutput signal to the handleOutput slot
    connect(process, &QProcess::readyReadStandardOutput, this, &Vocale::handleOutput);

    isCapturing = true;
    qDebug() << "Starting audio capture...";
}

void Vocale::stopCapture()
{
    if (process && process->state() == QProcess::Running) {
        qDebug() << "Stopping the process...";
        process->terminate();
        process->waitForFinished();
    } else {
        qDebug() << "No process running to stop.";
    }
    isCapturing = false;
}

void Vocale::handleOutput()
{
    // Capture the output from the Python script
    QString output = process->readAllStandardOutput().trimmed();
    qDebug() << "Process Output: " << output;  // Debugging the output from the Python script

    // Check if the output is empty, and if so, check for errors
    if (output.isEmpty()) {
        QString errorOutput = process->readAllStandardError().trimmed();
        qDebug() << "Process Error Output: " << errorOutput;
    }

    // Process the output from the Python script
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        qDebug() << "Processing line: " << line;  // Debugging each line

        if (line.contains("Recognized text:")) {
            QString recognizedText = line.mid(QString("Recognized text:").length()).trimmed();

            // Debugging the recognized text
            qDebug() << "Recognized Text: " << recognizedText;

            if (!recognizedText.isEmpty()) {
                qDebug() << "Emitting textCaptured with: " << recognizedText;  // Debugging the text being emitted
                emit textCaptured(recognizedText);  // Emit the recognized text
            } else {
                qDebug() << "No recognized text in the output.";
            }
        } else {
            qDebug() << "Line does not contain recognized text.";
        }
    }
}
