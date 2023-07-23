#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
#include <cstring>

#include <algorithm>

/**
* @brief Max config file size in symbols can be read
*/
#define MAX_FILE_SIZE 4096

#include <iostream>
static std::fstream logfile;

#define LOGFILE_OPEN logfile.open("commissionConfigurer.log", std::ios_base::out | std::ios_base::app)
#define LOGFILE_WRITE(a) logfile << a
#define LOGFILE_CLOSE logfile.close()

inline void write_info(const std::string what)
{
    std::cout << "[ " << what << " ]" << std::endl;
    LOGFILE_OPEN;
    LOGFILE_WRITE(std::string("INFO: [ ") + what + " ]\n");
    LOGFILE_CLOSE;
}

inline void write_warning(const std::string what)
{
    std::cout << "[ \033[33m" << what << "\033[0m ]" << std::endl;
    LOGFILE_OPEN;
    LOGFILE_WRITE(std::string("WARNING: [ ") + what + " ]\n");
    LOGFILE_CLOSE;
}

inline void write_success(const std::string what)
{
    std::cout << "[ \033[32m" << what << "\033[0m ]" << std::endl;
    LOGFILE_OPEN;
    LOGFILE_WRITE(std::string("SUCCESS: [ ") + what + " ]\n");
    LOGFILE_CLOSE;
}

inline void write_err(const std::string what, const std::string errText)
{
    std::cout << "[ \033[31m" << what << "\033[0m ] with text: [ " << errText << " ]" << std::endl;
    LOGFILE_OPEN;
    LOGFILE_WRITE(std::string("ERROR: [ ") + what + " ] WITH TEXT: [ " + errText + " ]\n");
    LOGFILE_CLOSE;
}





#include "encryption.h"

class Encryptor
{
    public:
        virtual ~Encryptor() = default;

        Encryptor(std::string key)
        {
            if (key.length() != 32)
            {
                throw std::runtime_error("Invalid key length!");
            }
            std::string & temp = const_cast<std::string &>(m_key);
            temp = key;
        }

        std::string encrypt(const std::string input);
        std::string decrypt(const std::string input);

    protected:
        const std::string m_key;
        bool m_status = false;
};

class FileModifier
{
    public:
        struct Config
        {
            std::string name;
            std::map<std::string, std::string> settings;
            std::string config_hash; // TODO: Use it in commission and create here
            bool is_correct = true;

            /**
            * @brief Changes contains of struct to desired one
            * @param presetName Name of preset to use
            * @return True if success, false if error
            * @note Available presets:
            *       "mining"        Struct with settings "miner", "is_primary", "wallet", "pool" etc.
            *       "commission"    Struct with settings "active", "period_s", "time_s", "miner_count", etc.
            */
            bool usePreset(const std::string presetName);

            static void showAvailablePresets()
            {
                const std::vector<std::string> PRESETS =
                {
                    "mining", "commission"
                };

                for (auto & preset : PRESETS)
                {
                    write_info(preset);
                }
            }
        };

        FileModifier(Encryptor * enc) : m_encryptor(enc) { logfile.open("commissionConfigurer.log", std::ios_base::out | std::ios_base::trunc); logfile.close(); }
        virtual ~FileModifier() = default;

        bool createFile(std::string configFile, std::string & errorText);
        bool openFile  (std::string configFile, std::string & errorText);

        bool readFile(std::string & errorText);
        bool saveFile(std::string & errorText);

        bool saveBackup(std::string & errorText);
        bool loadBackup(std::string & errorText);

        void showAllNames();
        bool getConfigByName(Config ** ppConfig, const std::string configName, std::string & errorText);
        void addConfig(const std::string configPreset);
        void removeConfig(Config ** ppConfig);

    protected:
        Encryptor * m_encryptor;

        std::fstream m_configFile;

        std::string m_configFilePath;

        std::vector <Config> m_configsArr;

        std::string translate(Config & cfg);
        Config translate(std::string & cfg);
};

#endif // FILEMODIFIER_H
