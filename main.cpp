#include <iostream>
#include <sstream>      // command & argument
#include <fstream>      // file handling
#include <filesystem>   // file check
#include <string>
#include <vector>


struct Column
{
    std::string name;
    std::string type;
};

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
            bool validSchema = true;
            std::vector<Column> columns;

            std::string schema;
            std::getline(ss, schema);


            schema.erase(0, schema.find_first_not_of(" \t"));

            // Missing Schema
            if (schema.empty())
            {
                std::cout << "\nError: Schema is required here.";
                validSchema = false; // 1
            }
            else
            {
                if (schema.front() == '(' && schema.back() == ')')
                {
                    schema.erase(0, 1);
                    schema.pop_back();

                    // Empty Schema
                    if (schema.empty())
                    {
                        std::cout << "\nError: Schema cannot be empty.";
                        validSchema = false; // 2
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

                            if (columnName.empty() || columnType.empty())
                            {
                                std::cout << "\nError: Each column must have a name and a type.";
                                validSchema = false; // 3
                            }

                            if (columnType != "TEXT" && columnType != "INTEGER" && columnType != "REAL")
                            {
                                std::cout << "\nError: Unsupported data type.";
                                validSchema = false; // 4
                            }


                            Column currentColumn;
                            currentColumn.name = columnName;
                            currentColumn.type = columnType;

                            columns.push_back(currentColumn);
                        }
                    }
                }
                else
                {
                    std::cout << "\nError: Schema must be enclosed in parenthesis.";
                    validSchema = false; // 5
                }
            }

           

            if (!validSchema)
            {
                std::cout << "\nError: no CSV created!";
            }

            else if (argument.empty())
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
                        for (size_t i = 0; i < columns.size(); i++)
                        {
                            file << columns[i].name;
                            if (i < columns.size() - 1)
                            {
                                file << ",";
                            }
                        }

                        file << "\n";
                        file.close();

                        std::string schemaFileName = "data/" + argument + ".schema";
                        std::ofstream schemaFile(schemaFileName);

                        if (schemaFile.is_open())
                        {
                            for (size_t i = 0; i < columns.size(); i++)
                            {
                                schemaFile << columns[i].name << " " << columns[i].type << "\n";
                            }

                            schemaFile.close();
                        }
                        else
                        {
                            std::cout << "\nFailed to create schema file.";
                        }
                        
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