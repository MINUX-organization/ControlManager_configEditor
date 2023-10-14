#ifndef PROCESSINVOKER_H
#define PROCESSINVOKER_H

#include <QString>

namespace ConfigsLib
{

class ProcessInvoker
{
public:
    static int invoke(const QString & processName, const int timeout = 10000);
    static int invoke(const QString & processName, const QStringList & processArgs, const int timeout = 10000);
    static int invoke(const QString & processName, const QStringList & processArgs, QString & processOutput, const int timeout = 10000);
};

}

#endif // PROCESSINVOKER_H
