#include <iostream>

#include "include/filemodifier.h"

void checkUp(Encryptor ** enc);
bool init_all(FileModifier & fm, std::string & filename);
void editConfig(std::string & answer, FileModifier & fm);

int main()
{
    write_info("Welcome to Commission Config file editor!");
    Encryptor * enc = nullptr;
    try
    {
        checkUp(&enc);
    }
    catch (std::exception & ex)
    {
        write_err("Initialization error", ex.what());
    }


    if (enc != NULL) // Double-check
    {
        FileModifier fm(enc);

        std::string answer, errorText;
        bool done = false;



        /*

        while (!done)
        {
            // User interface
            write_warning("Command list is below");
            write_info("\"start\" to list all config names");
            write_info("\"quit\" to exit the program");

            std::cout << ">>> "; std::cin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c) { return std::tolower(c); });

            if (answer == "quit")
            {
                done = true;
            } else if (answer == "start")
            {
                system("clear");

                write_info("Write file name to create or edit:");
                std::cout << ">>> "; std::cin >> answer;

                init_all(fm, answer);

                try
                {
                    // Try to read file
                    fm.readFile(errorText) ? write_success("File have been read") : write_err("File read error", errorText);

                    editConfig(answer, fm);
                }
                catch(std::exception &ex)
                {
                    write_err("Runtime error", ex.what());
                }
            }
            if (done)
            {
                write_info("Do you sure want to exit program? y/n");
                std::cout << ">>> "; std::cin >> answer;
                done = answer == "y";
            }
        }
        */
        delete enc; // Free
    }
    write_info("Thanks for using Commission Config file editor");
    return 0;
}

void checkUp(Encryptor ** enc)
{
    write_warning("INSERT ENCRYPTION KEY:");
    std::string key;
    #warning "DEBUG ONLY"
    key = "o5eiVVO+8fz5eWtS6eItUY5WVyen1NBSgnd1mUrtWD0="; /* std::cin >> key; */ key = base64_decode(key);
    std::string testPlain = "Aboba", testDecrypt, testEncrypt;
    if ( encryptPacketAES(testPlain, key, testEncrypt) )
    {
        *enc = new Encryptor(key);
        write_success("KEY ACCEPTED");
    }
    else
    {
        write_err("KEY INVALID", getErrorText());
        throw std::runtime_error("Invalid encryption key!");
    }
}


bool init_all(FileModifier & fm, std::string & filename)
{
    write_info("Initialization...");

    std::string errTxt;
    bool operationResult {false};

    operationResult = fm.openFile(filename, errTxt);
    if (operationResult)
    {
        write_success("File open success");
    }
    else
    {
        write_err("File open error", errTxt);

        write_info("Creating new file");
        operationResult = fm.createFile(filename, errTxt);

        operationResult ? write_success("File created") : write_err("File create error", errTxt);
    }
    return operationResult;
}

void editConfig(std::string & answer, FileModifier & fm)
{
    bool done = false;
    FileModifier::Config * currentConfig; std::map<std::string, std::string>::iterator settingIterator;
    std::string errorText;

    while (!done)
    {
        system("clear");
        write_info("CONFIG FILE HEADERS BEGIN");
        fm.showAllNames();
        write_info("CONFIG FILE HEADERS END");

        write_warning("Command list is below");
        write_info("\"add\" to add config");
        write_info("\"edit\" to edit desired config");
        write_info("\"remove\" to remove config");
        write_info("\"save\" to save changes");
        write_info("\"load\" to load backup");
        write_info("\"back\" for return to menu");
        std::cout << ">>> "; std::cin >> answer;
        std::transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c) { return std::tolower(c); });

        if (answer == "back")
        {
            return;
        } else if (answer == "add")
        {
            write_success("Choose preset for config");
            FileModifier::Config::showAvailablePresets();
            write_warning("IF CONFIG ALREADY EXIST, IT WILL NOT BE CREATED");
            std::cout << ">>> "; std::cin >> answer;
            fm.addConfig(answer);

        } else if (answer == "remove")
        {
            write_success("Choose config header");
            std::cout << ">>> "; std::cin >> answer;
            fm.getConfigByName(&currentConfig, answer, errorText) ? write_success("Config find success") : write_err("Config find error", errorText);
            fm.removeConfig(&currentConfig);

        } else if (answer == "edit")
        {
            while (!done)
            {
                write_info("CONFIG FILE HEADERS BEGIN");
                fm.showAllNames();
                write_info("CONFIG FILE HEADERS END");
                write_success("Choose config header or write \"back\" to save changes and return");
                std::cout << ">>> "; std::cin >> answer;
                if (answer == "back")
                {
                    done = true;
                }
                else
                {
                    if (fm.getConfigByName(&currentConfig, answer, errorText))
                    {
                        write_info("Settings are represented as");
                        write_success("NAME : VALUE");
                        write_warning("Write setting name to edit or \"cancel\" for return to menu");
                        write_warning("Write \"configName\"to edit name of config");
                        for (auto & s : currentConfig->settings)
                        {
                            write_info(s.first + " : " + s.second);
                        }
                        std::cout << ">>> "; std::cin >> answer;
                        if (answer == "cancel")
                        {
                            done = true;
                            system("clear");
                        } else if (answer == "configName")
                        {
                            std::cout << ">>> "; std::cin >> answer;
                            currentConfig->name = answer;
                        }
                        else
                        {
                            settingIterator = currentConfig->settings.find(answer);
                            if (settingIterator != currentConfig->settings.end())
                            {
                                write_success("Write new value");
                                std::cout << ">>> "; std::cin >> answer;
                                settingIterator->second = answer;
                            }
                            else
                            {
                                write_err("No such setting name in config", answer);
                            }
                        }
                        system("clear");
                    }
                    else
                    {
                        write_err("No such config name stated", answer);

                    }
                }
            }
            done = false;

        } else if (answer == "save")
        {
            // Save backup
            fm.saveBackup(errorText) ? write_success("Create / save backup success") : write_err("Create / save backup error", errorText);

            // Save file
            fm.saveFile(errorText) ? write_success("Save success") : write_err("Save error", errorText);

        } else if (answer == "load")
        {
            // Load backup
            fm.loadBackup(errorText) ? write_success("Load backup success") : write_err("Load backup error", errorText);

            fm.readFile(errorText) ? write_success("Read after backup load success") : write_err("Read after backup load error", errorText);

        } else
        {
            write_err("No such command listed", answer);
        }
    }
}

