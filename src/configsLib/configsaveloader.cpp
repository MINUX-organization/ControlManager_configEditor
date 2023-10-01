#include "configsaveloader.h"

#include <fstream>

using namespace ConfigsLib;

struct ConfigSaveLoader::Impl
{
    std::fstream m_configFile;
};

ConfigSaveLoader::ConfigSaveLoader()
{

}


ConfigSaveLoader::~ConfigSaveLoader()
{

}
