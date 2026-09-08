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
            std::string schema;
            std::getline(ss, schema);


            schema.erase(0, schema.find_first_not_of(" \t"));

            if (schema.empty())
            {
                std::cout << "\nError: Schema is required here.";
            }
            else
            {
                if (schema.front() == '(' && schema.back() == ')')
                {
                    schema.erase(0, 1);
                    schema.pop_back();

                    if (schema.empty())
                    {
                        std::cout << "\nError: Schema cannot be empty.";
                    }
                    else
                    {
                        std::stringstream schemaStream(schema);
                        std::string column;

                        while (std::getline(schemaStream, column, ','))
                        {
                            column.erase(0, column.find_first_not_of(" \t"));
                            
                            std::stringstream columnStream(column);

                            std::string columnName;
                            std::string columnType;

                            columnStream >> columnName;
                            columnStream >> columnType;
                        }
                    }

                    
                }
                else
                {
                    std::cout << "\nError: Schema must be enclosed in parenthesis.";
                }
            }

           


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
            std::cout << "\ndatabase: " << argument;
            std::cout << "\nschema: " << schema;
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