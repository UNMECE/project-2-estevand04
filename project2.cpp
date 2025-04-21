#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Student {
    protected: 
    std::string firstName;
    std::string lastName;
    float gpa;
    int gradYr;
    std::string gradSem;
    int enrollYr;
    std::string enrollSem;
    std::string Lvl; //meaning undergrad or grad
    
    public:
    Student()
    : firstName(""), lastName(""), gpa(0.0), gradYr(0), gradSem(""), enrollYr(0), enrollSem(""), Lvl("") {}
    
    virtual ~Student() {}
    
    //the setters
    void setName(const std::string& first, const std::string& last) {
        firstName = first;
        lastName = last;
    }
    
    void setGPA(float g) { gpa = g; }
    void setGradYr(int y) { gradYr = y; }
    void setGradSem(const std::string& s) { gradSem = s; }
    void setEnrollYr(int y) { enrollYr = y; }
    void setEnrollSem(const std::string& s) { enrollSem = s; }
    void setLvl(const std::string& l) {Lvl = l;}
    
    //the getters
    std::string getName() const { return firstName + " " + lastName; }
    float getGPA() const { return gpa; }
    int getGradYr() const { return gradYr; }
    std::string getGradSem() const { return gradSem; }
    int getEnrollYr() const { return enrollYr; }
    std::string getEnrollSem() const { return enrollSem; }
    std::string getLvl() const { return Lvl; }
    
    //the pure virual fucntion:
    virtual void print(std::ostream& os) const=0;
};

class artStudent : public Student {
    private:
    std::string artEmphasis; // such as art studio, history, and education
    
    public: 
    artStudent() : artEmphasis("art studio") {}
    ~artStudent() {}
    
    void setArtEmp(const std::string& emphasis) {
        artEmphasis = emphasis;
    }
    
    std::string getArtEmp() const {
        return artEmphasis;
    }
    
    void print(std::ostream& os) const override {
        os << "art student: " << getName() << ", GPA: " << getGPA() << ", enrolled: " << enrollSem << " " << enrollYr << ", graduating: " << gradSem << " " << gradYr << ", Level: " << Lvl << ", emphasis: " << artEmphasis << "\n";
        
    }
};

class physStudent : public Student {
    private: 
    std::string concentration; //such as bio, earth, or planetary sciences
    
    public: 
    physStudent() : concentration("bio") {}
    ~physStudent() {}
    
    void setConcentration(const std::string& conc) {
        concentration = conc;
        }
        
        std::string getConcentration() const {
            return concentration;
        }
        
        void print(std::ostream& os) const override {
            os << "Physics Student: " << getName() << ", GPA: " << getGPA() << ", Enrolled: " << enrollSem << " " << enrollYr << ", graduating: " << gradSem << " " <<gradYr << ", level: " << Lvl << ", concentration " << concentration << "\n";
            
        }
};

int main() { 
    std::vector<artStudent*> artStudents;
    std::vector<physStudent*> physStudents;
    
    //creating 5 art students
    int i;
    for(i=0; i<5; ++i) {
        artStudent* a = new artStudent();
        a->setName("artFirst" + std::to_string(i), "Last" + std::to_string(i));
        a->setGPA(3.5 + 0.1 * i);
        a->setEnrollYr(2025);
        a->setEnrollSem("fall");
        a->setGradYr(2029);
        a->setGradSem("spring");
        a->setLvl("undergrad"); 
        a->setArtEmp( i % 3 == 0 ? "art history" : ( i % 3 == 1 ? "art studio" : "art education"));
        artStudents.push_back(a);
    }   
    
    //creating 5 physics students 
    
    for(i = 0; i < 5; ++i) {
        physStudent* p = new physStudent();
         p->setName("PhysicsFirst" + std::to_string(i), "Last" + std::to_string(i));
        p->setGPA(3.4 + 0.1 * i);
        p->setEnrollYr(2019);
        p->setEnrollSem("Spring");
        p->setGradYr(2023);
        p->setGradSem("Fall");
        p->setLvl("grad");
        p->setConcentration(i % 2 == 0 ? "Biophysics" : "Earth and Planetary Sciences");
        physStudents.push_back(p);
    }
    
    //writing all student information into a data file
    std::ofstream outfile("studentInfo.dat");
    if(!outfile) {
        std::cerr << "error opening file.\n";
        return 1;
    }
    
    for (auto* a : artStudents) {
        a->print(outfile);
    }
    
    for (auto* p : physStudents) {
        p->print(outfile);
    }
    
    outfile.close();
    
    //clean up to memory
    for(auto* a : artStudents) delete a;
    for(auto* p : physStudents) delete p;
    
    return 0;
}
