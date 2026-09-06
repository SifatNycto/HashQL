#include <iostream>
#include <sstream>
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