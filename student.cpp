#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

class Student {
    private:
    int roll;
    string name;
    vector<int> marks;
    int total;
    double percentage;

    public:
    Student()
    {
        roll=0;
        total=0;
        percentage=0.0;
        marks.resize(5,0);
    }

    void input()
    {
        cout<<"Enter roll number: "<<endl;
        cin>>roll;
        cout<<"Enter name: "<<endl;
        cin>>name;
        cout<<"Enter marks for 5 subjects (integers): "<<endl;
        for(int i=0; i<5; i++)
        {
            cout<<"Subject "<<(i+1)<<": ";
            cin>>marks[i];
        }
        calculateResult();
    }
    
    void calculateResult()
    {
        for(int m:marks)
        {
            total+=m;
        }
        percentage =(total/5.0);
    }

    void display()
    {
        cout<<"Roll Number: "<<roll<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Marks: ";
        for(int i=0; i<5; i++)
        {
            cout<<marks[i];
            if(i<4)
            cout<<", ";
        }
        cout<<endl;
        cout<<"Total Marks: "<<total<<endl;
        cout<<"Percentage: "<<percentage<<"%"<<endl;
        cout<<"--------------------------"<<endl;
    }

    int getRoll() const { return roll; }

    string toCSV() const {
        stringstream ss;
        ss << roll << "," << name;
        for (int m : marks) {
            ss << "," << m;
        }
        ss << "," << total << "," << percentage;
        return ss.str();
    }

    static Student fromCSV(const string& line) {
        stringstream ss(line);
        string token;

        int roll;
        string name;
        vector<int> marks(5);
        int total;
        double percentage;

        getline(ss, token, ',');
        roll = stoi(token);

        getline(ss, name, ',');

        for (int i = 0; i < 5; ++i) {
            getline(ss, token, ',');
            marks[i] = stoi(token);
        }
        if (getline(ss, token, ',')) {
            total = stoi(token);
        } else {
            total = 0;
        }

        if (getline(ss, token, ',')) {
            percentage = stod(token);
        } else {
            percentage = 0.0;
        }

        Student s;
        s.roll = roll;
        s.name = name;
        s.marks = marks;
        s.total = total;
        s.percentage = percentage;
        return s;
    }
};

void loadfromCSV(const string& filename, vector<Student>& students) {
    ifstream file(filename);
    if (!file.is_open()) {
        return; 
    }
    string line;
    if (getline(file, line)) {
        if (line.find("Roll") == string::npos) {
            students.push_back(Student::fromCSV(line));
        }
    }
    while (getline(file, line)) {
        if (!line.empty())
            students.push_back(Student::fromCSV(line));
    }
    file.close();
}

void saveToCSV(const string& filename, const vector<Student>& students) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }
    file << "Roll,Name,Mark1,Mark2,Mark3,Mark4,Mark5,Total,Percentage\n";

    for (const auto& s : students) {
        file << s.toCSV() << "\n";
    }
    file.close();
}

void addStudents(vector<Student>& students) {
    Student s;
    s.input();
    students.push_back(s);
    cout << "Student record added.\n";
}

void displayAllStudents( vector<Student>& students) {
    if (students.empty()) {
        cout << "No records to display.\n";
        return;
    }
    cout << "\n=== All Student Records ===\n";
    for (auto& s : students) {
        s.display();
    }
}

void searchStudent(vector<Student>& students)
{
    if(students.empty())
    {
        cout<<"No record available."<<endl;
        return;
    }

    int roll;
    cout<<"Enter roll number to search: ";
    cin>>roll;

    bool found=false;
    for( auto& s: students)
    {
        if(s.getRoll()==roll)
        {
            cout<<"Record found: "<<endl;
            s.display();
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"No student found with roll number "<<roll<<endl;
    }
}

int main()
{
    vector<Student> students;
    string filename = "students.csv";

    loadfromCSV(filename, students);
    
    int choice;
    do{
        cout<<"----- Student Result Manangement System -----"<<endl;
        cout<<"1. Add Students Record"<<endl;
        cout<<"2. Display All Students Records"<<endl;
        cout<<"3. Search Record by Roll Number"<<endl;
        cout<<"4. Save and Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
            {
                addStudents(students);
                break;
            }
            case 2:
            {
                displayAllStudents(students);
                break;
            }
            case 3:
            {
                searchStudent(students);
                break;
            }
            case 4:
            {
                saveToCSV(filename, students);
                cout<<"Data saved to "<<filename<<". Exiting..."<<endl;
                break;
            }
            default:
            {
                cout<<"Invalid choice. Please try again."<<endl;
                break;
            }
        }
    }
    while(choice!=4);
    return 0;
}