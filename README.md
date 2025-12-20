# School Management System (C Console Application)

This is a simple, console-based application written in C, designed to manage personal records, which has been repurposed as a basic "School Management System."

## Features

- **Password Protection:** Access to the system is protected by a password.
- **Record Management:**
    - Add new records (time, name, place, duration, note).
    - View records (whole day or specific time).
    - Edit existing records.
    - Delete records.
- **Password Management:** Change the system password.

## Technology Stack

- **Language:** C
- **Environment:** Console/Terminal
- **Data Storage:** Binary files (`.dat` or similar, named by date)

## Compilation and Running

The code has been updated for portability and should compile on most modern systems (Linux, macOS, Windows) using a standard C compiler like GCC.

1. **Compile:**
   ```bash
   gcc "school management project/school.c" -o school_manager
   ```

2. **Run:**
   ```bash
   ./school_manager
   ```

## Code Improvements

The code has been refactored to address critical security and portability issues:

- **Security:** Replaced unsafe `gets()` with safe `fgets()` to prevent buffer overflows.
- **Portability:** Removed non-standard Windows-specific functions (`getch()`, `system("cls")`, `fflush(stdin)`) and replaced them with portable C standard library equivalents.

## Author

Hassan Kamau
