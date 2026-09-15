# HashQL

**HashQL** is a lightweight, CSV-based Database Management System (DBMS) prototype built in C++.

It provides a simple command-line interface with a custom SQL-inspired command syntax for creating structured databases, storing records, viewing data, searching records, and updating existing records.

The project focuses on implementing core database concepts using standard C++ features such as file I/O, string parsing, vectors, and structured data representation.

---

## Features

- Interactive command-line interface
- Database and schema creation
- CSV-based persistent data storage
- Separate schema metadata files
- Record insertion
- Formatted record display
- Record search by ID
- Record update by ID
- Basic command validation and error handling
- Built using standard C++ libraries

---

## Commands

| Command | Description |
|---|---|
| `CREATE` | Creates a database with a defined schema |
| `ADD` | Adds a new record |
| `SHOW` | Displays stored records |
| `SEARCH` | Searches for a record by ID |
| `UPDATE` | Updates an existing record |
| `HELP` | Displays available commands |
| `EXIT` | Exits HashQL |

---

## System Architecture

HashQL follows a simple layered workflow from user input to persistent storage:

```text
                         USER
                           │
                           ▼
                    HQL> COMMAND
                           │
                           ▼
                 ┌───────────────────┐
                 │  Command Parsing  │
                 └─────────┬─────────┘
                           │
                           ▼
                 ┌───────────────────┐
                 │ Operation Handler │
                 └─────────┬─────────┘
                           │
              ┌────────────┼────────────┐
              │            │            │
              ▼            ▼            ▼
           CREATE         ADD       SHOW / SEARCH
              │            │            │
              └────────────┼────────────┘
                           │
                           ▼
                 ┌───────────────────┐
                 │ Record / Schema   │
                 │    Processing     │
                 └─────────┬─────────┘
                           │
                           ▼
                 ┌───────────────────┐
                 │  File Storage     │
                 └─────────┬─────────┘
                           │
              ┌────────────┴────────────┐
              ▼                         ▼
        Database Data              Schema Metadata
          `.csv`                    `.schema`
              │                         │
              └────────────┬────────────┘
                           ▼
                         OUTPUT
                           │
                           ▼
                          USER
```

### Architecture Flow

```text
User Input
    ↓
Command Parser
    ↓
Operation Selection
    ↓
Schema / Record Processing
    ↓
CSV / Schema File
    ↓
Result
    ↓
User
```

The architecture keeps the main responsibilities conceptually separated:

- **Command Interface** — receives user commands through `HQL>`.
- **Command Parsing** — identifies commands, database names, and required arguments.
- **Operation Handling** — performs database operations such as creation, insertion, search, display, and update.
- **Record & Schema Processing** — represents and processes structured database information.
- **File Storage** — maintains persistent records in CSV files and schema metadata in `.schema` files.

---

## Workflow

The general HashQL workflow is:

```text
             User
               │
               ▼
          Enter Command
               │
               ▼
        Parse Command
               │
               ▼
      Identify Operation
               │
               ▼
     Perform Database Task
               │
               ▼
     Read / Modify Storage
               │
               ▼
          Generate Result
               │
               ▼
             Output
```

For the main database lifecycle:

```text
CREATE
  ↓
Define Schema
  ↓
Create Storage
  ↓
ADD Records
  ↓
SHOW Data
  ↓
SEARCH Records
  ↓
UPDATE Records
```

---

## Storage Model

HashQL uses a simple file-based storage system.

Each database consists of two files:

```text
data/
├── students.csv
└── students.schema
```

### CSV File

Stores the actual records.

```csv
id,name,age
25204009,Sifat,21
```

### Schema File

Stores the structure and data types of the database.

```text
id INTEGER
name TEXT
age INTEGER
```

Currently supported data types are:

- `TEXT`
- `INTEGER`
- `REAL`

Keeping the data and schema separately provides a clear distinction between **stored records** and **database metadata**.

---

## Data Structures

HashQL uses simple C++ structures to represent database information.

### Column

```cpp
struct Column
{
    std::string name;
    std::string type;
};
```

Represents a database column and its associated type.

### Record

```cpp
struct Record
{
    std::vector<std::string> values;
};
```

Represents a single database record.

Records can be managed in memory using:

```cpp
std::vector<Record>
```

---

## Technologies

- **Language:** C++
- **Storage:** CSV + `.schema` files
- **Interface:** Command-Line Interface (CLI)
- **Compiler:** g++
- **Libraries:** C++ Standard Library

Key C++ components used include:

```text
iostream
sstream
fstream
filesystem
string
vector
iomanip
```

---

## Example

A typical HashQL session:

```text
HashQL Database
Type HELP for available commands.

HQL> CREATE students (id INTEGER, name TEXT, age INTEGER)

HQL> ADD students

HQL> SHOW students

HQL> SEARCH students 25204009

HQL> UPDATE students 25204009

HQL> SHOW students
```

---

## Project Structure

```text
HashQL/
├── main.cpp
├── README.md
├── .gitignore
└── data/
    ├── <database>.csv
    └── <database>.schema
```

### Structure Overview

| Path | Purpose |
|---|---|
| `main.cpp` | Main HashQL application and database logic |
| `README.md` | Project documentation |
| `.gitignore` | Git ignore rules |
| `data/` | Persistent database files |
| `<database>.csv` | Stored records |
| `<database>.schema` | Database schema metadata |

---

## Getting Started

### Requirements

- C++ compiler with standard library support
- `g++`
- Terminal / command prompt

### Clone

```bash
git clone https://github.com/SifatNycto/HashQL.git
cd HashQL
```

### Compile

```bash
g++ main.cpp -o main
```

### Run

#### Windows

```powershell
.\main
```

#### Linux / macOS

```bash
./main
```

Once launched, HashQL provides the interactive prompt:

```text
HQL>
```

Type `HELP` to view the available commands.

---

## Project Focus

HashQL is built as a practical C++ project to explore the fundamentals of:

- Database management systems
- Persistent file storage
- Schema representation
- Command parsing
- Data structures
- Algorithms
- File handling
- Structured data processing

Rather than relying on an external database engine, HashQL implements its core functionality directly in C++ using the standard library.
<!-- 
---

## Author

**Mehedi Hasan Sifat**

B.Sc. in Computer Science and Engineering  
Canadian University of Bangladesh

GitHub: [SifatNycto](https://github.com/SifatNycto)

---

## License

This project is developed as an educational and academic project. -->
