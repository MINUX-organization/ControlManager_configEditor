#include "../include/filemodifier.h"

bool FileModifier::saveBackup(std::string & errorText)
{
    m_configFile.close();

    m_configFile.open(m_configFilePath, std::ios_base::in);
    std::fstream m_configFile_cpy("config_backup.ini", std::ios_base::out | std::ios_base::trunc);

    if (!m_configFile.is_open())
    {
        errorText = std::string("File open error") + std::strerror(errno);
        return false;
    } else if (!m_configFile_cpy.is_open())
    {
        errorText = std::string("Backup file open error") + std::strerror(errno);
        return false;
    }

    std::string readbuf;
    for (int i = 0; (i < MAX_FILE_SIZE) && !m_configFile.eof(); i++)
    {
        readbuf += m_configFile.get();
    }
    m_configFile.close();

    readbuf.pop_back();

    m_configFile_cpy << readbuf;
    m_configFile_cpy.close();
}

bool FileModifier::loadBackup(std::string & errorText)
{
    if (m_configFile.is_open())
    {
        m_configFile.close();
    }

    m_configFile.open(m_configFilePath, std::ios_base::out | std::ios_base::trunc);
    std::fstream m_configFile_cpy("config_backup.ini", std::ios_base::in);

    if (!m_configFile.is_open())
    {
        errorText = std::string("File open error") + std::strerror(errno);
        return false;
    } else if (!m_configFile_cpy.is_open())
    {
        errorText = std::string("Backup file open error") + std::strerror(errno);
        return false;
    }

    std::string readbuf;
    for (int i = 0; (i < MAX_FILE_SIZE) && !m_configFile_cpy.eof(); i++)
    {
        readbuf += m_configFile_cpy.get();
    }
    m_configFile_cpy.close();

    readbuf.pop_back();

    m_configFile << readbuf;
    m_configFile.close();
}



bool FileModifier::createFile(std::string configFile, std::string & errorText)
{
    if (configFile.length() < 1)
    {
        errorText = "Filename is too short!";
        return false;
    }

    m_configFile.open(configFile, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

    if (!m_configFile.is_open())
    {
        errorText = std::strerror(errno);
        return false;
    }

    m_configFilePath = configFile;
    m_configFile.close();

    return true;
}

bool FileModifier::openFile  (std::string configFile, std::string & errorText)
{
    if (configFile.length() < 1)
    {
        errorText = "Filename is too short!";
        return false;
    }

    m_configFile.open(configFile, std::ios_base::in | std::ios_base::out);

    if (!m_configFile.is_open())
    {
        errorText = std::strerror(errno);
        return false;
    }

    m_configFilePath = configFile;
    m_configFile.close();
    return true;
}


bool FileModifier::readFile(std::string & errorText)
{
    bool result = false;

    m_configFile.open(m_configFilePath, std::ios_base::in | std::ios_base::out);

    // Read data from file
    std::string readBuf;
    for (int i = 0; (i < MAX_FILE_SIZE) && (!m_configFile.eof()); i++)
    {
        readBuf += m_configFile.get();
    }
    m_configsArr.clear();

    if (readBuf.length() > 10)
    {
        readBuf.pop_back(); readBuf += '\n';
        std::replace_if(readBuf.begin(), readBuf.end(), [](auto s){ return s == 0x0A; }, '\n' );

        {
            std::string encryptedBuf, decryptedBuf; std::string::iterator endlinePos;
            for (std::string::iterator s = readBuf.begin() + 1; s < readBuf.end(); s++)
            {
                endlinePos = std::find(s, readBuf.end(), '\n');

                encryptedBuf = std::string(s, endlinePos);
                s = endlinePos + 1;

                decryptedBuf += m_encryptor->decrypt(encryptedBuf) + '\n';
            }
            readBuf = decryptedBuf;
        }

        if (readBuf.length() < 1)
        {
            write_err("Error parsing", getErrorText());
        }
        else
        {
            Config anotherConfig;

            std::string readLine; std::string::iterator endlinePos;
            for (std::string::iterator s = readBuf.begin(); s < readBuf.end(); s++)
            {
                endlinePos = std::find(s, readBuf.end(), '\n');

                readLine = std::string(s, endlinePos);
                s = endlinePos;

                anotherConfig = translate(readLine);

                // Check if there's error translating
                if (!anotherConfig.is_correct)
                {
                    errorText = anotherConfig.name;
                    break;
                }

                // If no errors, add to vector and clear
                m_configsArr.push_back(anotherConfig);
            }

            // Test if errors occured
            if (anotherConfig.is_correct)
            {
                result = true;
            }
        }
    }
    else
    {
        errorText = "File is empty";
    }

    return result;
}

bool FileModifier::saveFile(std::string & errorText)
{
    bool result = false;

    std::string buffer;

    m_configFile.open(m_configFilePath, std::ios_base::out | std::ios_base::trunc);

    if (m_configFile.is_open())
    {
        result = true;
    }

    for (auto & conf : m_configsArr)
    {
        buffer = translate(conf);

        buffer = m_encryptor->encrypt(buffer);

        m_configFile << std::endl << buffer << std::endl;
    }

    m_configFile.close();
    return result;
}
