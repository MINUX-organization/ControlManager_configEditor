#include "../include/filemodifier.h"

std::string Encryptor::encrypt(const std::string input)
{
    if (input.length() < 1)
    {
        return "";
    }

    std::string result;

    m_status = encryptPacketAES(input, m_key, result);

    if (m_status)
    {
        result = base64_encode(result);
    }

    return result;
}

std::string Encryptor::decrypt(const std::string input)
{
    if (input.length() < 1)
    {
        return "";
    }

    std::string result, decodedInput;

    decodedInput = base64_decode(input);

    m_status = decryptPacketAES(decodedInput, m_key, result);

    return result;
}

void FileModifier::showAllNames()
{
    for (auto & cfg : m_configsArr)
    {
        write_info(cfg.name);
    }
}

bool FileModifier::getConfigByName(FileModifier::Config ** ppConfig, const std::string configName, std::string & errorText)
{
    Config * pConf = *ppConfig = nullptr;

    for (auto & m_cfg : m_configsArr)
    {
        if (m_cfg.name == configName)
        {
            pConf = &m_cfg;
            break;
        }
    }
    if (pConf == nullptr)
    {
        errorText = "Config not found";
    }
    else
    {
        *ppConfig = pConf;
    }

    return *ppConfig != nullptr;
}

void FileModifier::addConfig(const std::string configPreset)
{
    if (configPreset.length() > 0)
    {
        Config anotherCfg;
        anotherCfg.usePreset(configPreset);
        m_configsArr.push_back(anotherCfg);
    }
}

void FileModifier::removeConfig(FileModifier::Config ** ppConfig)
{
    auto conf = std::find_if(m_configsArr.begin(), m_configsArr.end(), [&ppConfig](auto & conf) { return conf.name == (*ppConfig)->name; });

    if (conf != m_configsArr.end())
    {
        m_configsArr.erase(conf);
    }
}
