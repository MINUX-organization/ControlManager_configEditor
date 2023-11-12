#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <memory>
#include <vector>

#include <msgpack.hpp>

#include "encryption.h"

namespace ConfigsLib
{

/*
/// Example struct
struct testStruct
{
    std::string abobaData {"TEST DATA IS DATA"};
    int intData {1};
    MSGPACK_DEFINE(abobaData, intData)
};

/// Example of using
testStruct ts;
ts.abobaData = "Not a test data";
ts.intData = 0;

ConfigsLib::ConfigFile cf;

try
{
    std::string buffer = cf.compressClass(ts);

    testStruct otherTs = cf.decompressClass<testStruct>(buffer);

    qDebug() << otherTs.abobaData.c_str() << otherTs.intData;
}
catch (std::exception & ex)
{
    qDebug() << ex.what();
}
*/

class ConfigFile
{
    friend class ConfigWorker;
public:
    ConfigFile(bool clearAndSaveOnDestroy = true);
    ~ConfigFile();

    template <typename T>
    static std::string compressClass(const T & classObject, bool encrypted = false, const std::string & encryptionKey = "");

    template <typename T>
    static T decompressClass(const std::string & serializedClass, bool encrypted = false, const std::string & encryptionKey = "");

    bool createFile(const std::string & filePath);
    bool setFile(const std::string & filePath);
    std::string filePath() const;

    bool addClass(const std::string & value);
    std::string getClass(const uint64_t index);

    bool save();
    void load();

    void clearBuffer();
    void clearFile();

    uint64_t classesCount() const;
    const char * errorText() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};




template <typename T>
T ConfigFile::decompressClass(const std::string &serializedClass, bool encrypted, const std::string & encryptionKey)
{
    T result;

    if (encrypted)
    {
        std::string decryptedBuffer;

        if (encryptionKey == "")
        {
            throw std::runtime_error("[compressClass] Not provided encryption key");
        }

        if (!decryptPacketAES(base64_decode(serializedClass), encryptionKey, decryptedBuffer))
        {
            throw std::runtime_error( std::string("[compressClass] Error decrypting data: ") + getErrorText() );
        }

        try
        {
            msgpack::object_handle oh;
            msgpack::unpack(oh, decryptedBuffer.c_str(), decryptedBuffer.size());
            msgpack::object obj = oh.get();
            obj.convert(result);
        }
        catch (std::exception & ex)
        {
            throw std::runtime_error(std::string("[compressClass] Error unpacking data. Error message: ") + ex.what());
        }
    }
    else
    {
        try {
            msgpack::object_handle oh;
            msgpack::unpack(oh, serializedClass.c_str(), serializedClass.size());
            msgpack::object obj = oh.get();
            obj.convert(result);
        }
        catch (std::exception & ex)
        {
            throw std::runtime_error(std::string("[compressClass] Error unpacking data. Error message: ") + ex.what());
        }
    }

    return result;
}


template <typename T>
std::string ConfigFile::compressClass(const T &classObject, bool encrypted, const std::string & encryptionKey)
{
    std::stringstream buffer;

    try
    {
        msgpack::pack(buffer, classObject);
    }
    catch (std::exception & ex)
    {
        throw std::runtime_error(std::string("[compressClass] Error packing data. Error message: ") + ex.what());
    }

    if (encrypted)
    {
        std::string encryptedBuffer;
        std::string serializedClass = buffer.str();

        if (encryptionKey == "")
        {
            throw std::runtime_error("[compressClass] Not provided encryption key");
        }

        if (!encryptPacketAES(serializedClass, encryptionKey, encryptedBuffer))
        {
            throw std::runtime_error( std::string("[compressClass] Error encrypting data: ") + getErrorText() );
        }

        return base64_encode(encryptedBuffer);
    }

    return buffer.str();
}

}

#endif // CONFIGFILE_H
