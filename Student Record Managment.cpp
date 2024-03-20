#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char filename[] = "student_records.txt";
const int MAX_STUDENTS = 100;

struct Student {
    int rollNumber;
    char* name;
    int age;
    int phoneNum;
    char* dep;
};

void readFromFile(Student*& students, int& size) {
    ifstream file(filename);

    size = 0;
    while (file >> students[size].rollNumber) {
        file.ignore(); // Ignore the space
        students[size].name = new char[50];
        file.getline(students[size].name, 50, ' ');

        file >> students[size].age >> students[size].phoneNum;

        file.ignore(); // Ignore the space
        students[size].dep = new char[50];
        file.getline(students[size].dep, 50);

        size++;
    }

    file.close();
}

void addStudent(Student*& students, int& size) {
    if (size < MAX_STUDENTS) {
        cout << "Enter Roll Number: ";
        cin >> students[size].rollNumber;

        cout << "Enter Name: ";
        students[size].name = new char[50];
        cin.ignore(); // Clear newline character from previous input
        cin.getline(students[size].name, 50);

        cout << "Enter Age: ";
        cin >> students[size].age;

        cout << "Enter Phone Number: ";
        cin >> students[size].phoneNum;

        cout << "Enter Department: ";
        cin.ignore();
        students[size].dep = new char[50];
        cin.getline(students[size].dep, 50);

        // Save the new student to the file
        ofstream file(filename, ios::app);

        if (file.is_open()) {
            file << students[size].rollNumber << " " << students[size].name << " " << students[size].age << " " << students[size].phoneNum << " " << students[size].dep << "\n";
            file.close();
            cout << "Student added successfully.\n";
        }
        else {
            cout << "Error saving to file.\n";
        }

        size++;
    }
    else {
        std::cout << "Maximum number of students reached. Cannot add more.\n";
    }
}

void deleteStudent(Student*& students, int& size) {
    if (size == 0) {
        cout << "No records available. Cannot delete.\n";
        return;
    }

    int rollNumberToDelete;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumberToDelete;

    int indexToDelete = -1;

    for (int i = 0; i < size; ++i) {
        if (students[i].rollNumber == rollNumberToDelete) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        // Delete dynamic memory for names and departments
        delete[] students[indexToDelete].name;
        delete[] students[indexToDelete].dep;

        // Shift elements in the array
        for (int i = indexToDelete; i < size - 1; ++i) {
            students[i] = students[i + 1];
        }

        // Set the last element to default values
        students[size - 1].rollNumber = 0;
        students[size - 1].name = nullptr;
        students[size - 1].age = 0;
        students[size - 1].phoneNum = 0;
        students[size - 1].dep = nullptr;

        size--;

        // Update the file
        ofstream file(filename);

        if (file.is_open()) {
            for (int i = 0; i < size; ++i) {
                file << students[i].rollNumber << " " << students[i].name << " " << students[i].age << " " << students[i].phoneNum << " " << students[i].dep << "\n";
            }

            file.close();
            cout << "Student with Roll Number " << rollNumberToDelete << " deleted successfully.\n";
        }
        else {
            cout << "Error updating file.\n";
        }
    }
    else {
        cout << "Student with Roll Number " << rollNumberToDelete << " not found\n";
    }
}

void searchStudent(Student* students, int size) {
    if (size == 0) {
        cout << "No records available.\n";
        return;
    }

    int rollNumberToSearch;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumberToSearch;

    bool found = false;

    for (int i = 0; i < size; ++i) {
        if (students[i].rollNumber == rollNumberToSearch) {
            cout << "Student found:\n";
            cout << "Roll Number: " << students[i].rollNumber << "\n";
            cout << "Name: " << students[i].name << "\n";
            cout << "Age: " << students[i].age << "\n";
            cout << "Phone Number: " << students[i].phoneNum << "\n";
            cout << "Department: " << students[i].dep << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumberToSearch << " not found\n";
    }
}

void displayAllStudents(Student* students, int size) {
    if (size == 0) {
        cout << "No records available.\n";
        return;
    }

    cout << "--------------------------------------------------------------------------\n";
    cout << "\nAll student records:\n";
    for (int i = 0; i < size; ++i) {
        cout << "Roll Number: " << students[i].rollNumber << "\n";
        cout << "Name: " << students[i].name << "\n";
        cout << "Age: " << students[i].age << "\n";
        cout << "Phone Number: " << students[i].phoneNum << "\n";
        cout << "Department: " << students[i].dep << "\n\n";
    }
}

int main() {
    Student* students = new Student[MAX_STUDENTS];
    int size = 0;

    // Reading existing records from file
    readFromFile(students, size);

    // Display a message if no records are found
    if (size == 0) {
        cout << "No records available.\n";
    }
    cout << "\t\t ** Student Record Management **\n";
    int choice;
    do {

        cout << "\n\t\t\t1. Add Student\n";
        cout << "\t\t\t2. Delete Student\n";
        cout << "\t\t\t3. Search Student\n";
        cout << "\t\t\t4. Display All Students\n";
        cout << "\t\t\t5. Exit Program\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(students, size);
            break;
        case 2:
            deleteStudent(students, size);
            break;
        case 3:
            searchStudent(students, size);
            break;
        case 4:
            displayAllStudents(students, size);
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 5);

    // Clean up dynamic memory
    for (int i = 0; i < size; ++i) {
        delete[] students[i].name;
        delete[] students[i].dep;
    }
    delete[] students;

    return 0;
}