#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <msgpack.hpp>
#include <string>

namespace ConfigsLib
{

struct ConfigurationStruct
{
public:
    int64_t value(std::string key)
    {
        int64_t result = 0;
        try
        {
            std::map<std::string, std::string>::iterator keyPos = keyMap.find(key);

            if (keyPos == keyMap.end())
                return 0;

            result = std::stoi(keyPos->second);

        } catch (std::invalid_argument & ex)
        {
            return 0;
        }
        return result;
    }

    std::string value(std::string key)
    {
        std::map<std::string, std::string>::iterator keyPos = keyMap.find(key);

        if (keyPos == keyMap.end())
            return "";

        return keyPos->second;
    }

private:
    std::map<std::string, std::string> keyMap;
    MSGPACK_DEFINE(keyMap)
};

class Interpretator
{
public:
    Interpretator(const std::string & filePath);
    ~Interpretator();

protected:
    ConfigurationStruct m_sysInfo;
    ConfigurationStruct m_depInfo;

    ConfigurationStruct m_reserved_1;
    ConfigurationStruct m_reserved_2;

    std::vector<ConfigurationStruct> m_configs;
};

}

#endif // INTERPRETATOR_H
