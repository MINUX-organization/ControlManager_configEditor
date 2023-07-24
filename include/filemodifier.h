#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
#include <cstring>

#include <algorithm>

// For SHA256 hashing
#include <openssl/evp.h>
#include <cstring>
#include <iomanip>

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


inline std::string sha256(const std::string& str)
{
    if (str.empty()) {
        return "";
    }
    unsigned char hash[EVP_MAX_MD_SIZE];
    std::memset(hash, 0, sizeof(hash));
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    if (!mdctx || !md) {
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    EVP_DigestInit_ex(mdctx, md, nullptr);
    if (!EVP_DigestUpdate(mdctx, str.c_str(), str.size())) {
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    unsigned int len;
    if (!EVP_DigestFinal_ex(mdctx, hash, &len)) {
        EVP_MD_CTX_free(mdctx);
        return "";
    }
    EVP_MD_CTX_free(mdctx);
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < len; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
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


    public:
        static std::string translate(Config & cfg)
        {
            std::string result;

            nlohmann::json translator_cfg_to_json;

            translator_cfg_to_json["name"] = cfg.name;

            for (auto & field : cfg.settings)
            {
                translator_cfg_to_json[field.first] = field.second;
            }

            std::string hashBuffer = translator_cfg_to_json.dump();

            translator_cfg_to_json["hash"] = sha256(hashBuffer);

            write_info(std::string("Hash created: ") + sha256(hashBuffer));

            result = translator_cfg_to_json.dump();

            return result;
        }

        static Config translate(std::string & cfg)
        {
            Config result;
            try
            {
                nlohmann::json translator_json_to_cfg;
                nlohmann::json hashTest;

                translator_json_to_cfg = nlohmann::json::parse(cfg);

                for (auto& [key, value] : translator_json_to_cfg.items())
                {
                    if ((key != "name") && (key != "hash"))
                    {
                        result.settings[key] = value;
                        hashTest[key] = value; // Remember to test for correct hash
                    }
                }

                result.name = hashTest["name"] = translator_json_to_cfg["name"];

                std::string configHash  = translator_json_to_cfg["hash"];
                std::string hashBuffer = hashTest.dump();

                write_info(std::string("Hash input: ") + configHash);
                write_info(std::string("Hash check: ") + configHash);

                if (configHash != sha256(hashBuffer))
                {
                    throw std::runtime_error("Config hash is not equal!");
                }
            }
            catch (std::exception & ex)
            {
                result.name = "EXCEPTION: ";
                result.name += ex.what();

                result.is_correct = false;
            }

            return result;
        }
};

#endif // FILEMODIFIER_H
