#include "configfile.h"

#include "encryption.h"
#include <fstream>
#include <sstream>

#include <msgpack.hpp>

using namespace ConfigsLib;

struct ConfigFile::Impl
{
    std::string m_configPath;
    std::vector<std::string> m_classes;

    // Parses file inserted
    void updateData()
    {

    }
};

ConfigFile::ConfigFile() :
    m_pImpl { new Impl }
{

}

ConfigFile::~ConfigFile()
{

}

bool ConfigFile::setFile(const std::string &filePath)
{
    // Test if file exist
    std::fstream openTestFile(filePath, std::ios_base::in);
    if (!openTestFile.is_open())
    {
        return false;
    }

    // Set file
    m_pImpl->m_configPath = filePath;

    // Update configuratio using file
    m_pImpl->updateData();

    return true;
}

std::string ConfigFile::filePath() const
{
    return m_pImpl->m_configPath;
}

void ConfigFile::addClass(const std::string value)
{

}
