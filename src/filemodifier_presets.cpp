#include "../include/filemodifier.h"



bool FileModifier::Config::usePreset(const std::string presetName)
{
    bool result = false;

    if (presetName == "mining") // Mining preset of config struct
    {
        result = true;
        name = "miningPreset";

        settings["miner"] = "lolminer";

        settings["is_primary"] = "y";

        settings["algorithm"]   = "deafultAlgorithm";
        settings["wallet"]      = "deafultWallet";
        settings["pool"]        = "deafultPool";
        settings["port"]        = "0";

    } else if (presetName == "commission") // Commission settings preset of config struct
    {
        result = true;

        name = "commissionPreset";

        settings["active"]          = "y";
        settings["period_m"]        = "60";
        settings["time_s"]          = "60";
        settings["miner_count"]     = "1";

    } else // Invalid preset name, or did not set
    {
        name = "Undefined";
    }

    return result;
}
