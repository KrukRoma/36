#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Student 
{
private:
    string name;
    int id;
    int age;
    string major;

public:
    Student(string name, int id, int age, string major)
        : name(name), id(id), age(age), major(major) {}

    string getName() const { return name; }
    int getId() const { return id; }
    int getAge() const { return age; }
    string getMajor() const { return major; }

    void setName(const string& name) { this->name = name; }
    void setId(int id) { this->id = id; }
    void setAge(int age) { this->age = age; }
    void setMajor(const string& major) { this->major = major; }

    void print() const 
    {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Major: " << major << endl;
    }
};

class StudentDatabase 
{
private:
    vector<Student> students;

public:
    void addStudent(const Student& student) 
    {
        students.push_back(student);
    }

    void removeStudent(int id) 
    {
        for (auto it = students.begin(); it != students.end(); ++it) 
        {
            if (it->getId() == id) 
            {
                students.erase(it);
                cout << "Student with ID " << id << " has been removed." << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    Student* findStudent(int id) 
    {
        for (auto& student : students) 
        {
            if (student.getId() == id) 
            {
                return &student;
            }
        }
        return nullptr;
    }

    void listStudents() const 
    {
        for (const auto& student : students) 
        {
            student.print();
        }
    }

    void saveToFile(const string& filename) const 
    {
        ofstream file(filename);
        for (const auto& student : students) 
        {
            file << student.getId() << "," << student.getName() << "," << student.getAge() << "," << student.getMajor() << endl;
        }
    }

    void loadFromFile(const string& filename) 
    {
        ifstream file(filename);
        if (!file.is_open()) 
        {
            cerr << "Could not open file " << filename << endl;
            return;
        }

        students.clear();
        string line;
        while (getline(file, line)) 
        {
            string name, major;
            int id, age;
            size_t pos = 0;

            pos = line.find(',');
            id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            age = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            major = line;

            students.push_back(Student(name, id, age, major));
        }
    }

    void updateStudent(int id, const Student& newData) 
    {
        for (auto& student : students) 
        {
            if (student.getId() == id) 
            {
                student.setName(newData.getName());
                student.setAge(newData.getAge());
                student.setMajor(newData.getMajor());
                cout << "Student with ID " << id << " has been updated." << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void filterByMajor(const string& major) const 
    {
        for (const auto& student : students) 
        {
            if (student.getMajor() == major) 
            {
                student.print();
            }
        }
    }
};

void displayMenu() 
{
    cout << "Student Database Management System" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Remove Student" << endl;
    cout << "3. Find Student by ID" << endl;
    cout << "4. List All Students" << endl;
    cout << "5. Save Students to File" << endl;
    cout << "6. Load Students from File" << endl;
    cout << "7. Update Student" << endl;
    cout << "8. Filter Students by Major" << endl;
    cout << "9. Exit" << endl;
}

int main() 
{
    StudentDatabase db;
    int choice;

    while (true) 
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 9) 
        {
            break;
        }

        switch (choice) 
        {
        case 1: 
        {
            string name, major;
            int id, age;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Major: ";
            cin.ignore();
            getline(cin, major);
            db.addStudent(Student(name, id, age, major));
            break;
        }
        case 2: 
        {
            int id;
            cout << "Enter ID of student to remove: ";
            cin >> id;
            db.removeStudent(id);
            break;
        }
        case 3: 
        {
            int id;
            cout << "Enter ID of student to find: ";
            cin >> id;
            Student* student = db.findStudent(id);
            if (student) 
            {
                student->print();
            }
            else 
            {
                cout << "Student with ID " << id << " not found." << endl;
            }
            break;
        }
        case 4: 
        {
            db.listStudents();
            break;
        }
        case 5: 
        {
            string filename;
            cout << "Enter filename to save to: ";
            cin >> filename;
            db.saveToFile(filename);
            break;
        }
        case 6: 
        {
            string filename;
            cout << "Enter filename to load from: ";
            cin >> filename;
            db.loadFromFile(filename);
            break;
        }
        case 7: 
        {
            int id;
            cout << "Enter ID of student to update: ";
            cin >> id;
            string name, major;
            int age;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new Age: ";
            cin >> age;
            cout << "Enter new Major: ";
            cin.ignore();
            getline(cin, major);
            db.updateStudent(id, Student(name, id, age, major));
            break;
        }
        case 8: 
        {
            string major;
            cout << "Enter Major to filter by: ";
            cin.ignore();
            getline(cin, major);
            db.filterByMajor(major);
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}