#include <iostream>
#include <sstream>      // command & argument
#include <fstream>      // file handling
#include <filesystem>   // file check
#include <string>

int main()
{
    std::string command;

    std::cout << "\n" << "HashQL Database";
    std::cout << "\n" << "Type HELP for available commands.";

    while (true)
    {
        std::cout << "\n" << "HQL> ";
        std::getline(std::cin, command);

        std::stringstream ss(command);
        std::string keyword;
        std::string argument;
        ss >> keyword;
        ss >> argument;


        if (keyword == "HELP")
        {
            std::cout << "\n" << "HashQL commands: ";
            std::cout << "\n" << "  HELP";
            std::cout << "\n" << "  EXIT";
        }

        else if (keyword == "CREATE")
        {
            if (argument.empty())
            {
                std::cout << "\nUsage: CREATE <filename>";
            }
            
            else
            {
                std::string filename = "data/" + argument + ".csv";

                if (std::filesystem::exists(filename))
                {
                    std::cout << "\nDatabase '" << argument << "' already exists.";
                }

                else
                {
                    std::ofstream file(filename);

                    if (file.is_open())
                    {
                        std::cout << "\nDatabase '" << argument << "' created successfully.";
                        file.close();
                    }

                    else
                    {
                        std::cout << "\nFailed to create database.";
                    }
                }
            }

            
        }

        else if (keyword == "EXIT")
        {
            std::cout << "\n" << "Goodbye!";
            break;
        }

        else
        {
            std::cout << "\n " << "Unknown command. Type HELP.";
        }
    }


    return 0;
}