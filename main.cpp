#include <iostream>
#include <sstream>      // command & argument
#include <fstream>      // file handling
#include <filesystem>   // file check
#include <string>
#include <vector>
#include <iomanip>      // white space manipulation


struct Column
{
    std::string name;
    std::string type;
};

struct Record
{
    std::vector<std::string> values;
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
        std::string searchValue;

        ss >> keyword;
        ss >> argument;


// CREATE block....................
        if (keyword == "CREATE")
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


// ADD block.............
        else if (keyword == "ADD")
        {
            std::string schemaFileName = "data/" + argument + ".schema";

            std::ifstream schemaFile(schemaFileName);

            if (!schemaFile.is_open())
            {
                std::cout << "\nFailed to open schema file.";
            }
            else
            {
                std::string line;
                std::vector<Column> columns;

                while (std::getline(schemaFile, line))
                {
                    std::stringstream columnStream(line);
                    
                    std::string columnName;
                    std::string columnType;

                    columnStream >> columnName;
                    columnStream >> columnType;

                    Column currentColumn;
                    currentColumn.name = columnName;
                    currentColumn.type = columnType;

                    columns.push_back(currentColumn);
                }

                schemaFile.close();

                std::cout << "\nDatabase '" << argument << "' loaded.";

                Record record;

                for (size_t i = 0; i < columns.size(); i++)
                {
                    std::string value;
                    std::cout << "\nEnter " << columns[i].name << ": ";
                    std::getline(std::cin, value);
                    record.values.push_back(value);
                }

                std::string filename = "data/" + argument + ".csv";
                std::ofstream file(filename, std::ios::app);

                if (!file.is_open())
                {
                    std::cout << "\nFailed to open database file.";
                }
                else
                {
                    for (size_t i = 0; i < columns.size(); i++)
                    {
                        file << record.values[i];
                        if (i < columns.size() - 1)
                        {
                            file << ",";
                        }
                    }

                    file << "\n";
                    file.close();

                    std::cout << "\nRecord added successfully.";
                }
                
             
            }
        }


// UPDATE block...........................
        else if (keyword == "UPDATE")
        {
            ss >> searchValue;

            if (argument.empty() || searchValue.empty())
            {
                std::cout << "\nUsage: UPDATE <filename> <id>";
            }
            else
            {
                std::string fileName = "data/" + argument + ".csv";
                std::ifstream file(fileName);

                if (!file.is_open())
                {
                    std::cout << "\nError: Database doesn't exist.";
                }
                else
                {
                    std::string line;
                    std::string header;

                    std::getline(file, header);
                    
                    std::vector<Record> records;

                    while (std::getline(file, line))
                    {
                        std::stringstream rowStream(line);
                        std::string value;

                        Record record;

                        while (std::getline(rowStream, value, ','))
                        {
                            record.values.push_back(value);
                        }

                        records.push_back(record);
                    }

                    file.close();

                    bool found = false;

                    for (size_t i = 0; i < records.size(); i++)
                    {
                        if (!records[i].values.empty() && records[i].values[0] == searchValue)
                        {
                            found = true;
                            // std::cout << "\nRecord found!";
                            // break;

                            for (size_t j = 0; j < records[i].values.size(); j++)
                            {
                                std::string value;
                                
                                std::cout << "\nEnter new value for field " << j+1 << ": ";
                                std::getline(std::cin, value);

                                records[i].values[j] = value;
                            }


                            break;
                        }
                    }

                    if (!found)
                    {
                        std::cout << "\nRecord not found.";
                    }
                    else
                    {
                        std::ofstream output(fileName);

                        if (!output.is_open())
                        {
                            std::cout << "\nFailed to save database.";
                        }
                        else
                        {
                            output << header << "\n";

                            for (size_t i = 0; i < records.size(); i++)
                            {
                                for (size_t j = 0; j < records[i].values.size(); j++)
                                {
                                    output << records[i].values[j];

                                    if (j < records[i].values.size() - 1)
                                    {
                                        output << ",";
                                    }
                                }

                                output << "\n";
                            }

                            std::cout << "\nRecord updated successfully.";
                            output.close();
                        }
                    }
                }
            }
        }        


// SHOW block...................
        else if (keyword == "SHOW")
        {
            if (argument.empty())
            {
                std::cout << "\nUsage: SHOW <filename>";
            }
            else
            {
                std::string fileName = "data/" + argument + ".csv";
                std::ifstream file(fileName);

                if (!file.is_open())
                {
                    std::cout << "\nError: Can't load database or database doesn't exist";
                }
                else
                {
                    std::cout << "\nDatabase '" << argument << "' opened.\n";

                    std::string line;

                    bool isHeader = true;
                    
                    std::vector<std::string> headers;

                    while (std::getline(file, line))
                    {
                        if (isHeader)
                        {
                            std::stringstream headerStream(line);
                            std::string header;

                            while (std::getline(headerStream, header, ','))
                            {
                                headers.push_back(header);
                            }

                            for (size_t i = 0; i < headers.size(); i++)
                            {
                                std::cout << std::left << std::setw(12) << headers[i];
                            }
                            std::cout << "\n";
                            
                            for (size_t i = 0; i < headers.size(); i++)
                            {
                                std::cout << std::string(12, '-');
                            }
                            std::cout << "\n";

                            isHeader = false;
                            continue;
                        }

                        Record record;

                        std::stringstream rowStream(line);
                        std::string value;

                        while (std::getline(rowStream, value, ','))
                        {
                            record.values.push_back(value);
                        }

                        for (size_t i = 0; i < record.values.size(); i++)
                        {
                            std::cout << std::left << std::setw(12) << record.values[i];
                        }
                        std::cout << "\n";
                    }

                    file.close();
                }
            }
        }


// SEARCH block................................ 
        else if (keyword == "SEARCH")
        {
            ss >> searchValue;

            if (argument.empty() || searchValue.empty())
            {
                std::cout << "\nUsage: SEARCH <filename> <value>";
            }
            else
            {
                std::string fileName = "data/" + argument + ".csv";
                std::ifstream file(fileName);

                if (!file.is_open())
                {
                    std::cout << "\nError: Can't load database or data ase doesn't exist";
                }
                else
                {
                    std::string line;

                    std::getline(file, line);

                    bool found = false;

                    while (std::getline(file, line))
                    {
                        std::stringstream rowStream(line);
                        std::string value;

                        Record record;

                        while (std::getline(rowStream, value, ','))
                        {
                            record.values.push_back(value);
                        }

                        if (!record.values.empty() && record.values[0] == searchValue)
                        {
                            found = true;
                            std::cout << "\nFound: ";

                            for (size_t i = 0; i < record.values.size(); i++)
                            {
                                std::cout << std::left << std::setw(12) << record.values[i];
                            }
                            std::cout << "\n";
                        }
                    }

                    if (!found)
                    {
                        std::cout << "\nRecord not found.";
                    }

                    file.close();
                }

            }

        }
        

// HELP block.......................
        else if (keyword == "HELP")
        {
            std::cout << "\n" << "HashQL commands: ";
            std::cout << "\n" << ">> CREATE";
            std::cout << "\n" << ">> ADD";
            std::cout << "\n" << ">> UPDATE";
            std::cout << "\n" << ">> SHOW";
            std::cout << "\n" << ">> SEARCH";
            std::cout << "\n" << ">> HELP";
            std::cout << "\n" << ">> EXIT";
        }

        
// EXIT block..................
        else if (keyword == "EXIT")
        {
            std::cout << "\n" << "Goodbye!";
            break;
        }

// Invalid things...................        
        else
        {
            std::cout << "\n " << "Unknown command. Type HELP.";
        }
    }

    return 0;
}