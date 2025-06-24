#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cctype>

using namespace std;

string trim(const string &s); // prototype for trim

struct Student {
    string roll_no;
    string name;
    string class_name;
    string course;
    string mobile_no;
    string admission_year;
};

vector<Student> students;

bool isValidPhoneNumber(const string &phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void saveDataToFile(const string &filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "Error opening file for saving data." << endl;
        return;
    }
    for (const auto &s : students) {
        ofs << s.roll_no << '\n'
            << s.name << '\n'
            << s.class_name << '\n'
            << s.course << '\n'
            << s.mobile_no << '\n'
            << s.admission_year << '\n';
    }
    ofs.close();
}

void loadDataFromFile(const string &filename) {
    ifstream ifs(filename);
    if (!ifs) 
    {
        // File may not exist on first run, so no error message needed
        return;
    }
    students.clear();
    while (true) {
        Student s;
        if (!getline(ifs, s.roll_no)) break;
        if (!getline(ifs, s.name)) break;
        if (!getline(ifs, s.class_name)) break;
        if (!getline(ifs, s.course)) break;
        if (!getline(ifs, s.mobile_no)) break;
        if (!getline(ifs, s.admission_year)) break;
        students.push_back(s);
    }
    ifs.close();
}

bool isDuplicateRollNo(const string &roll_no) {
    for (const auto &s : students) {
        if (s.roll_no == roll_no) {
            return true;
        }
    }
    return false;
}

void enter() {
    int ch = 0;
    cout << "\n********** ENTER STUDENT DATA **********\n";
    while (true) {
        cout << ">>> HOW MANY STUDENTS DO YOU WANT TO ENTER? ";
        if (!(cin >> ch) || ch <= 0) {
            cout << "[!] Please enter a valid positive number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(1, '\n'); // clear the newline character left in the buffer
            break;
        }
    }

    for (int i = 0; i < ch; i++) {
        Student s;
        cout << "\n----------------------------------------\n";
        cout << "ENTER THE DATA OF STUDENT " << students.size() + 1 << endl;
        cout << "----------------------------------------\n";
        while (true) {
            cout << ">>> ENTER ROLL NO: ";
            getline(cin, s.roll_no);
            s.roll_no = trim(s.roll_no);
            if (s.roll_no.empty()) {
                cout << "[!] Roll number cannot be empty." << endl;
            } else if (isDuplicateRollNo(s.roll_no)) {
                cout << "[!] Duplicate roll number found. Please enter a unique roll number." << endl;
            } else {
                break;
            }
        }
        do {
            cout << ">>> ENTER NAME: ";
            getline(cin, s.name);
            s.name = trim(s.name);
            if (s.name.empty()) cout << "[!] Name cannot be empty." << endl;
        } while (s.name.empty());
        do {
            cout << ">>> ENTER CLASS / SECTION: ";
            getline(cin, s.class_name);
            s.class_name = trim(s.class_name);
            if (s.class_name.empty()) cout << "[!] Class/Section cannot be empty." << endl;
        } while (s.class_name.empty());
        do {
            cout << ">>> ENTER COURSE: ";
            getline(cin, s.course);
            s.course = trim(s.course);
            if (s.course.empty()) cout << "[!] Course cannot be empty." << endl;
        } while (s.course.empty());
        do {
            cout << ">>> ENTER MOBILE NO (10 digits): ";
            getline(cin, s.mobile_no);
            if (!isValidPhoneNumber(s.mobile_no)) {
                cout << "[!] Invalid phone number. Please enter exactly 10 digits." << endl;
            }
        } while (!isValidPhoneNumber(s.mobile_no));
        do {
            cout << ">>> ENTER ADMISSION YEAR (4 digits): ";
            getline(cin, s.admission_year);
            s.admission_year = trim(s.admission_year);
            if (s.admission_year.length() != 4 || !all_of(s.admission_year.begin(), s.admission_year.end(), ::isdigit)) {
                cout << "[!] Admission year must be a 4-digit number." << endl;
            }
        } while (s.admission_year.length() != 4 || !all_of(s.admission_year.begin(), s.admission_year.end(), ::isdigit));

        students.push_back(s);
    }
    saveDataToFile("students.txt");
}

void show() {
    if (students.empty()) {
        cout << "No Data is Entered" << endl;
    } else {
        for (size_t i = 0; i < students.size(); i++) {
            const Student &s = students[i];
            cout << "\nData of Student " << i + 1 << endl << endl;
            cout << "Roll NO: " << s.roll_no << endl;
            cout << "Name: " << s.name << endl;
            cout << "Class / Section:" << s.class_name << endl;
            cout << "Course: " << s.course << endl;
            cout << "Mobile NO: " << s.mobile_no << endl;
            cout << "Admission Year: " << s.admission_year << endl;
        }
    }
}

void search() {
    if (students.empty()) {
        cout << "No data is entered" << endl;
        return;
    }
    string rollno;
    cout << "Enter the roll no of student: ";
    getline(cin, rollno);
    bool found = false;
    for (const auto &s : students) {
        if (rollno == s.roll_no) {
            cout << "Roll NO: " << s.roll_no << endl;
            cout << "Name: " << s.name << endl;
            cout << "Class / Section :  " << s.class_name << endl;
            cout << "Course: " << s.course << endl;
            cout << "Mobile NO: " << s.mobile_no << endl;
            cout << "Admission Year: " << s.admission_year << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with roll no " << rollno << " not found." << endl;
    }
}

void update() {
    if (students.empty()) {
        cout << "No data is entered" << endl;
        return;
    }
    string rollno;
    cout << "Enter the roll no of student which you want to update: ";
    getline(cin, rollno);
    bool found = false;
    for (auto &s : students) {
        if (rollno == s.roll_no) {
            cout << "\nPrevious data" << endl << endl;
            cout << "Roll NO: " << s.roll_no << endl;
            cout << "Name: " << s.name << endl;
            cout << "Class / Section: " << s.class_name << endl;
            cout << "Course: " << s.course << endl;
            cout << "Mobile NO: " << s.mobile_no << endl;
            cout << "Admission Year: " << s.admission_year << endl;
            cout << "\nDo you want to update this record? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (confirm != 'y' && confirm != 'Y') {
                cout << "Update cancelled." << endl;
                return;
            }
            cout << "\nEnter new data" << endl << endl;
            string new_roll_no;
            while (true) {
                cout << "Enter Roll NO: ";
                getline(cin, new_roll_no);
                new_roll_no = trim(new_roll_no);
                if (new_roll_no.empty()) {
                    cout << "Roll number cannot be empty." << endl;
                } else if (new_roll_no != s.roll_no && isDuplicateRollNo(new_roll_no)) {
                    cout << "Duplicate roll number found. Please enter a unique roll number." << endl;
                } else {
                    s.roll_no = new_roll_no;
                    break;
                }
            }
            do {
                cout << "Enter Name: ";
                getline(cin, s.name);
                s.name = trim(s.name);
                if (s.name.empty()) cout << "Name cannot be empty." << endl;
            } while (s.name.empty());
            do {
                cout << "Enter Class / Section: ";
                getline(cin, s.class_name);
                s.class_name = trim(s.class_name);
                if (s.class_name.empty()) cout << "Class/Section cannot be empty." << endl;
            } while (s.class_name.empty());
            do {
                cout << "Enter Course: ";
                getline(cin, s.course);
                s.course = trim(s.course);
                if (s.course.empty()) cout << "Course cannot be empty." << endl;
            } while (s.course.empty());
            do {
                cout << "Enter Mobile NO (10 digits): ";
                getline(cin, s.mobile_no);
                if (!isValidPhoneNumber(s.mobile_no)) {
                    cout << "Invalid phone number. Please enter exactly 10 digits." << endl;
                }
            } while (!isValidPhoneNumber(s.mobile_no));
            do {
                cout << "Enter Admission Year (4 digits): ";
                getline(cin, s.admission_year);
                s.admission_year = trim(s.admission_year);
                if (s.admission_year.length() != 4 || !all_of(s.admission_year.begin(), s.admission_year.end(), ::isdigit)) {
                    cout << "Admission year must be a 4-digit number." << endl;
                }
            } while (s.admission_year.length() != 4 || !all_of(s.admission_year.begin(), s.admission_year.end(), ::isdigit));
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with roll no " << rollno << " not found." << endl;
    }
    saveDataToFile("students.txt");
}

string trim(const string &s) {
    size_t start = 0;
    while (start < s.size() && isspace(s[start])) start++;
    size_t end = s.size();
    while (end > start && isspace(s[end - 1])) end--;
    return s.substr(start, end - start);
}

void delete_record() {
    if (students.empty()) {
        cout << "No data is entered yet" << endl;
        return;
    }
    cout << "Press 1 to delete all records" << endl;
    cout << "Press 2 to delete a record by roll no" << endl;
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

    if (choice == 1) {
        cout << "Are you sure you want to delete all records? (y/n): ";
        char confirm;
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (confirm == 'y' || confirm == 'Y') {
            students.clear();
            saveDataToFile("students.txt");
            cout << "All records are deleted..!!" << endl;
        } else {
            cout << "Delete all records cancelled." << endl;
        }
    } else if (choice == 2) {
        string rollno;
        cout << "Enter the roll no of student to delete: ";
        getline(cin, rollno);
        rollno = trim(rollno);
        auto it = remove_if(students.begin(), students.end(), [&rollno](const Student &s) {
            return s.roll_no == rollno;
        });
        if (it != students.end()) {
            students.erase(it, students.end());
            saveDataToFile("students.txt");
            cout << "Record with roll no " << rollno << " deleted." << endl;
        } else {
            cout << "Student with roll no " << rollno << " not found." << endl;
        }
    } else {
        cout << "Invalid choice. Please press 1 or 2." << endl;
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    cout << "\n========================================\n";
    cout << "      STUDENT RECORD MANAGEMENT SYSTEM  \n";
    cout << "========================================\n";
    cout << "  1. Enter data\n";
    cout << "  2. Show data\n";
    cout << "  3. Search data\n";
    cout << "  4. Update data\n";
    cout << "  5. Delete data\n";
    cout << "  6. Quit\n";
    cout << "----------------------------------------\n";
    cout << ">>> ENTER YOUR CHOICE (1-6): ";
}

// --- Admin credential setup and login ---
bool loadAdminCredentials(string &username, string &password) {
    ifstream ifs("admin.txt");
    if (!ifs) return false;
    getline(ifs, username);
    getline(ifs, password);
    ifs.close();
    return true;
}

void saveAdminCredentials(const string &username, const string &password) {
    ofstream ofs("admin.txt");
    ofs << username << '\n' << password << '\n';
    ofs.close();
}

int main() {
    // Admin credential setup
    string admin_username, admin_password;
    if (!loadAdminCredentials(admin_username, admin_password)) {
        cout << "No admin credentials found. Please set up your admin account.\n";
        cout << "Set admin username: ";
        getline(cin, admin_username);
        cout << "Set admin password: ";
        getline(cin, admin_password);
        saveAdminCredentials(admin_username, admin_password);
        cout << "Admin account created! Please restart the program and log in.\n";
        return 0;
    }

    string username, password;
    int login_attempts = 0;
    const int max_attempts = 3;

    while (login_attempts < max_attempts) {
        cout << "Admin Login\n";
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);

        if (username == admin_username && password == admin_password) {
            cout << "Login successful!\n";
            break;
        } else {
            cout << "Invalid username or password. Please try again.\n";
            login_attempts++;
        }
    }

    if (login_attempts == max_attempts) {
        cout << "Maximum login attempts exceeded. Exiting program.\n";
        return 0;
    }

    loadDataFromFile("students.txt");
    int value;
    while (true) 
    {
        clearScreen();
        displayMenu();
        while (!(cin >> value) || value < 1 || value > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            displayMenu();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch (value) {
            case 1:
                enter();
                break;
            case 2:
                show();
                break;
            case 3:
                search();
                break;
            case 4:
                update();
                break;
            case 5:
                delete_record();
                break;
            case 6:
                char confirm;
                cout << "Are you sure you want to exit? (y/n): ";
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y') {
                    cout << "Thank you for using the Student Record Management System. Goodbye!" << endl;
                    return 0;
                } else {
                    break;
                }
            default:
                cout << "Invalid input. Please enter a number between 1 and 6." << endl;
                break;
        }
        cout << "Press Enter to continue...";
        cin.get();
    }
    return 0;
}
