#ifndef CONFIGTREE_H
#define CONFIGTREE_H

#include <memory>

#include "configfile.h"

namespace ConfigsLib
{

struct ConfigDir
{
    ConfigDir(const std::string & path) : path(path) {}
    const std::string path;
    std::vector<ConfigDir *> m_dirs;
    std::vector<ConfigFile *> m_configs;
};

class ConfigTree
{
public:
    ConfigTree();
    ~ConfigTree();

    bool addConfig(const std::string & virtualPath, const std::string & serializedClass);
    std::string config(const std::string & virtualPath); // Loads config by path like /commission/mining/GPUs/lolminer

    bool setBasePath(const std::string basePath);
    std::string basePath() const;

    bool save(const std::string & virtualPath);
    bool saveAll();
    void load(const std::string & virtualPath);
    void loadAll();

    void parseAll();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // CONFIGTREE_H
