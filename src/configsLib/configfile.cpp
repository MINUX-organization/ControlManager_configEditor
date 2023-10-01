#include "configfile.h"

#include <fstream>

using namespace ConfigsLib;

struct ConfigFile::Impl
{
    std::fstream m_configFile;
};

ConfigFile::ConfigFile()
{

}

ConfigFile::~ConfigFile()
{

}

template<typename T>
ConfigFile &ConfigFile::operator[](const T value)
{
    return *this;
}
