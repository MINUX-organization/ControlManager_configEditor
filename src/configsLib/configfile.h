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
ConfigsLib::testStruct ts;
ts.abobaData = "Not a test data";
ts.intData = 0;

ConfigsLib::ConfigFile cf;

std::string buffer = cf.compressClass(ts);

ConfigsLib::testStruct otherTs = cf.decompressClass<ConfigsLib::testStruct>(buffer);
*/

class ConfigFile
{
    friend class ConfigWorker;
public:
    ConfigFile();
    ~ConfigFile();

    bool setFile(const std::string & filePath);
    std::string filePath() const;

    template <typename T>
    std::string compressClass(const T & classObject)
    {
        std::stringstream buffer;
        msgpack::pack(buffer, classObject);
        return buffer.str();
    }

    void addClass(const std::string & uid, const std::string value);

    template <typename T>
    T decompressClass(const std::string & serializedClass)
    {
        testStruct result;
        msgpack::object_handle oh;
        msgpack::unpack(oh, serializedClass.c_str(), serializedClass.size());
        msgpack::object obj = oh.get();
        obj.convert(result);
        return result;
    }

    std::string loadClass(const std::string & uid);

    std::string configUid() const;
    std::vector<std::string> contentUids() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGFILE_H
