#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Person
{
protected:
    char mark;
    int id;
    string name;
protected: 
    Person(int id, const string& n):name(n)
    {
        this->id = id;
        mark = 'P';
    }
public:
    virtual ~Person()
    {
        cout<< "Person name: "<<name
            << " is dead"<<endl;
    }
public:
    virtual void CallMe() = 0;
};

class Student: public Person
{
private:
    int grade;

public:
    Student(int id, const string& name,int grade): Person(id,name)
    {
        this->grade = grade;
        this->mark = 'S';
    }
    virtual void CallMe()
    {
        cout<<"I am student: "
            << name
            <<" in grade "<< grade
            <<endl;
    }

    virtual ~Student()
    {
        cout << "Student named: "<< name
            << " is dead" <<endl;
    }
}; 

class GoodStudent: public Student
{
public:

    GoodStudent(int id, const string& name, int grade):Student(id, name, grade)
    {
        this->mark='G';
    }
    virtual ~GoodStudent()
    {
        cout << "Good student named: " << name <<" exits." <<endl;
    }

    void CallMe()
    {
        cout << "I am good student named:" << name <<endl;
    }
};

class A
{
    public: 
        int a;
        int b;
        char c;
};
int main()
{
//    cout << "clock:"
//         << clock() << endl;
//    srand(clock());
//    cout << "next random number:" << rand() <<endl;
    A* a = new A;
    Person* p = new Student(1, "tommmy", 6);
    p->CallMe();
    Student* s = dynamic_cast<Student*>(p);
    s->CallMe();

    Student& s2  = *s;
//    GoodStudent& gs = dynamic_cast<GoodStudent&> (s2);
    s2.CallMe();
    delete p;
    delete a;
}
