#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <memory>
#include <vector>

namespace ConfigsLib
{

class ConfigFile
{
    friend class ConfigWorker;
public:
    ConfigFile();
    ~ConfigFile();

    bool setFile(const std::string & filePath);
    std::string filePath() const;

    template <typename T>
    std::string compressFile(const T & classObject);
    void addClass(const std::string & uid, const std::string value);

    template <typename T>
    T compressFile(const std::string & serializedClass);
    std::string loadClass(const std::string & uid);

    std::string configUid() const;
    std::vector<std::string> contentUids() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGFILE_H
