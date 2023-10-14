#include "processinvoker.h"

#include <QDebug>
#include <QProcess>
#include <signal.h>

#define PROCESS_INVOKER_STATIC_LOGGING

#ifdef PROCESS_INVOKER_STATIC_LOGGING
template <typename T>
void log(const T & data)
{
    qDebug() << "[PROCESS INVOKER]: " << data << endl;
}
#endif // defined(PROCESS_INVOKER_STATIC_LOGGING) || defined(PROCESS_INVOKER_CLASS_LOGGING)

using namespace ConfigsLib;

int ProcessInvoker::invoke(const QString &processName, const int timeout)
{
    QProcess process;
    process.setProgram(processName);

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Starting process");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    process.start();

    if (!process.waitForStarted(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

    if (!process.waitForFinished(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log("Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING

        if (process.isOpen())
        {
            if (kill(process.pid(), SIGINT))
            {
                // Here will be SIGINT to main program
            }
#ifdef PROCESS_INVOKER_STATIC_LOGGING
            log("Process exit timeout, killed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        }

#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process not finished, kill succeed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Process finished normally");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    return process.exitCode();
}

int ProcessInvoker::invoke(const QString &processName, const QStringList &processArgs, const int timeout)
{
    QProcess process;
    process.setProgram(processName);
    process.setArguments(processArgs);

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Starting process");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    process.start();

    if (!process.waitForStarted(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

    if (!process.waitForFinished(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log("Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING

        if (process.isOpen())
        {
            if (kill(process.pid(), SIGINT))
            {
                // Here will be SIGINT to main program
            }
#ifdef PROCESS_INVOKER_STATIC_LOGGING
            log("Process exit timeout, killed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        }

#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process not finished, kill succeed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Process finished normally");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    return process.exitCode();
}

int ProcessInvoker::invoke(const QString &processName, const QStringList &processArgs, QString &processOutput, const int timeout)
{
    QProcess process;
    process.setProgram(processName);
    process.setArguments(processArgs);

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Starting process");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    process.start();

    if (!process.waitForStarted(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

    if (!process.waitForFinished(timeout))
    {
#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log("Process start timeout");
#endif // PROCESS_INVOKER_STATIC_LOGGING

        if (process.isOpen())
        {
            if (kill(process.pid(), SIGINT))
            {
                // Here will be SIGINT to main program
            }
#ifdef PROCESS_INVOKER_STATIC_LOGGING
            log("Process exit timeout, killed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        }

#ifdef PROCESS_INVOKER_STATIC_LOGGING
        log( "Process not finished, kill succeed");
#endif // PROCESS_INVOKER_STATIC_LOGGING
        return -1;
    }

    processOutput = process.readAllStandardOutput();

#ifdef PROCESS_INVOKER_STATIC_LOGGING
    log( "Process finished normally");
#endif // PROCESS_INVOKER_STATIC_LOGGING
    return process.exitCode();
}
