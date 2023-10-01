#ifndef CONFIGWORKER_H
#define CONFIGWORKER_H

#include <memory>

namespace ConfigsLib
{

class ConfigWorker
{
public:
    ConfigWorker();
    ~ConfigWorker();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGWORKER_H
