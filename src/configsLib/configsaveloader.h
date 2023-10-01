#ifndef CONFIGSAVELOADER_H
#define CONFIGSAVELOADER_H

#include <memory>

namespace ConfigsLib
{

class ConfigSaveLoader
{
public:
    ConfigSaveLoader();
    ~ConfigSaveLoader();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGSAVELOADER_H
