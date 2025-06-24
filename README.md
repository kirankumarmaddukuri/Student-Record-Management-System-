# 🎓 Student Record Management System 

A simple yet complete **Student Record Management System** built using **C++**, featuring CRUD operations, data persistence through file handling, a clean and enhanced CLI interface, and robust input validation. Ideal for managing basic student information like roll number, name, class, course, mobile number, and admission year.

---

## 🛠️ Features

- 📥 Add new student records (with validation)
- 📋 View all records
- 🔍 Search student by roll number
- ✏️ Update existing student data (with confirmation prompt)
- 🗑️ Delete a specific record or all records
- 💾 Save/load data from file (`students.txt`)
- 🔐 Admin login system with credential setup on first run
- 🔐 Validation for:
  - Unique roll number
  - Valid 10-digit mobile number
  - No empty fields; admission year must be a 4-digit number
- 🧼 **Enhanced CLI-based interface:**
  - ASCII borders and section headers for a visually appealing menu
  - Clear, consistent prompts and error messages
  - Input highlighting for user actions and errors
  - Confirmation prompts for updates and exiting the program
- 🚀 Ready for further GUI development

---

## 📂 File Structure

```
main.cpp          # Main source code file containing all program logic
students.txt      # Data file used to persist student records (auto-generated)
admin.txt         # Stores admin username and password (auto-generated on first run)
README.md         # Project documentation and overview
```

---

## 🚀 How to Use

1. Compile the program using a C++ compiler, for example:
   ```bash
   g++ main.cpp -o student_management
   ```

2. Run the executable:
   ```bash
   ./student_management
   ```

3. **On the first run:**
   - The program will prompt you to set an admin username and password.
   - These credentials are saved in `admin.txt` for future logins.
   - After setting credentials, restart the program and log in with your chosen username and password.

4. **On subsequent runs:**
   - You will be prompted to log in with the admin credentials you set previously.

5. Use the menu-driven interface to manage student records.
   - Enjoy the enhanced CLI with clear borders, prompts, and error messages.
   - All inputs are validated, and you will be re-prompted for invalid entries.
   - Confirmation is required before updating a record or exiting the program.

**To reset the admin credentials:**
Delete the `admin.txt` file and restart the program. You will be prompted to set new credentials.

---

## 🧩 How It Works

- The program stores student data in a vector of `Student` structs.
- Data is saved to and loaded from a text file (`students.txt`) to maintain persistence.
- Admin credentials are stored in `admin.txt` and required for login.
- Duplicate roll numbers are prevented during data entry and updates.
- Mobile numbers are validated to ensure exactly 10 digits.
- Admission year and all fields are validated for correctness.
- The user interacts with the program through an enhanced, user-friendly command-line menu.

---

## 📈 Potential Improvements

- Modularize code into multiple files or classes for better maintainability.
- Add unit tests to verify functionality.
- Implement sorting and filtering options.
- Create a graphical user interface (GUI) using a C++ GUI library.
- Use a database for scalable data storage.

---



