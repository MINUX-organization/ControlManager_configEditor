#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <memory>
#include <vector>

#include <msgpack.hpp>

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
    ConfigFile();
    ~ConfigFile();

    template <typename T>
    static std::string compressClass(const T & classObject);

    template <typename T>
    static T decompressClass(const std::string & serializedClass);

    bool setFile(const std::string & filePath);
    std::string filePath() const;

    void addClass(const std::string value);


    std::string loadClass(const uint64_t index);
    uint64_t configsCount() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};


template <typename T>
T ConfigFile::decompressClass(const std::string &serializedClass)
{
    T result;
    msgpack::object_handle oh;
    msgpack::unpack(oh, serializedClass.c_str(), serializedClass.size());
    msgpack::object obj = oh.get();
    obj.convert(result);
    return result;
}


template <typename T>
std::string ConfigFile::compressClass(const T &classObject)
{
    std::stringstream buffer;
    msgpack::pack(buffer, classObject);
    return buffer.str();
}

}

#endif // CONFIGFILE_H
