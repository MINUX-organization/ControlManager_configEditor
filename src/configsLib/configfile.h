#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <memory>

namespace ConfigsLib
{

class ConfigFile
{
public:
    ConfigFile();
    ~ConfigFile();

    void setFilePath(const std::string & filePath);
    std::string getFilePath() const;

    template <typename T>
    ConfigFile & operator[](const T value);

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGFILE_H
