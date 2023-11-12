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

    bool clearAndSaveOnDestroy {false};
    bool isParsing {false};

    std::string errorText;
};

ConfigFile::ConfigFile(bool clearAndSaveOnDestroy) :
    m_pImpl { new Impl }
{
    m_pImpl->clearAndSaveOnDestroy = clearAndSaveOnDestroy;
}

ConfigFile::~ConfigFile()
{
    if (!m_pImpl->clearAndSaveOnDestroy)
        return;

    save();
}

bool ConfigFile::createFile(const std::string &filePath)
{
    std::fstream openTestFile;
    openTestFile.open(filePath, std::ios::out);
    if (!openTestFile.is_open())
    {
        m_pImpl->errorText = std::string("File create error: ") + strerror(errno);
        return false;
    }
    openTestFile.close();

    m_pImpl->m_configPath = filePath;

    return true;
}

bool ConfigFile::setFile(const std::string &filePath)
{
    // Test if file exist
    std::fstream openTestFile(filePath, std::ios_base::in);
    if (!openTestFile.is_open())
    {
        m_pImpl->errorText = std::string("File open error: ") + strerror(errno);
        return false;
    }
    openTestFile.close();

    m_pImpl->m_configPath = filePath;

    return true;
}

std::string ConfigFile::filePath() const
{
    return m_pImpl->m_configPath;
}

bool ConfigFile::addClass(const std::string & value)
{
    if (m_pImpl->isParsing)
    {
        m_pImpl->errorText = "Is parsing";
        return false;
    }
    m_pImpl->m_classes.push_back(value);
    return true;
}

std::string ConfigFile::getClass(const uint64_t index)
{
    if (m_pImpl->isParsing)
    {
        m_pImpl->errorText = "Is parsing";
        return "";
    }

    if (m_pImpl->m_classes.size() <= index)
    {
        m_pImpl->errorText = "Invalid index";
        return "";
    }

    return m_pImpl->m_classes[index];
}

bool ConfigFile::save()
{
    std::fstream configFile(m_pImpl->m_configPath, std::ios_base::out);

    if (!configFile.is_open())
        return false;

    for (const std::string & str : m_pImpl->m_classes)
        configFile << str << std::endl;

    configFile.close();

    return true;
}
void ConfigFile::load()
{
    m_pImpl->isParsing = true;

    std::fstream configFile(m_pImpl->m_configPath, std::ios_base::in);
    if (!configFile.is_open())
    {
        m_pImpl->isParsing = false;
        return;
    }

    char buffer;
    std::string bufferStr;
    while (!configFile.eof())
    {
        while ((configFile.get(buffer) && (buffer != 0x0A)))
            bufferStr += buffer;

        m_pImpl->m_classes.push_back(bufferStr);
        bufferStr.clear();
    }
    configFile.close();

    if (m_pImpl->m_classes.size() > 0)
        m_pImpl->m_classes.pop_back(); // Remove empty string

    m_pImpl->isParsing = false;
}

void ConfigFile::clearBuffer()
{
    m_pImpl->m_classes.clear();
}

void ConfigFile::clearFile()
{
    std::fstream openTestFile(m_pImpl->m_configPath, std::ios_base::out | std::ios_base::trunc);
    if (!openTestFile.is_open())
    {
        m_pImpl->errorText = std::string("File open error: ") + strerror(errno);
        return;
    }
    openTestFile.close();
}
const char * ConfigFile::errorText() const { return m_pImpl->errorText.c_str(); }

uint64_t ConfigFile::classesCount() const
{
    if (m_pImpl->isParsing)
    {
        m_pImpl->errorText = "Is parsing";
        return 0;
    }
    return m_pImpl->m_classes.size();
}
