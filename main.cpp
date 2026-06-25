#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>
using namespace std;
class course{
    protected:
    string course_name;
    int credit_hrs;
    int t_marks;
    int obt_marks;
    public:
    course(){
      course_name=" ";
      credit_hrs=t_marks=obt_marks=0;  
    } 

    string get_course_name(){return course_name;}
    int get_credit_hrs(){return credit_hrs;}
    int get_t_marks(){return t_marks;}
    int get_obt_marks(){return obt_marks;}

    void input(int course_num){
        cout<<"Enter the name of course "<<course_num<<": ";
        getline(cin,course_name);
        cout<<"Enter credit hours of the course "<<course_num<<": ";
        cin>>credit_hrs;
        cin.ignore(1000,'\n');
        cout<<"Enter total marks of the course "<<course_num<<": ";
        cin>>t_marks;
        cin.ignore(1000,'\n');
        cout<<"Enter marks obtained in the course "<<course_num<<": ";
        cin>>obt_marks; 
        cin.ignore(1000,'\n');  
    }
    void set_data(string name, int hrs, int total, int obtained){
    course_name = name;
    credit_hrs = hrs;
    t_marks = total;
    obt_marks = obtained;
}
};
class student{
    protected:
    string s_name;
    string roll_no;
    int no_of_courses;
    vector<course>courses;
    bool found=false;
    int semester;
    public:
    student(){
        s_name=roll_no=" ";
        no_of_courses=0;
    } 
    void input(){
        cout<<"Enter your Roll no: ";
        getline(cin,roll_no);
        ifstream file("students.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Roll No: " + roll_no) != string::npos) {
                string nameLine;
                  getline(file, nameLine); //reads only next line which is name
                  s_name = nameLine.substr(6); 
                cout << "Welcome Back " << s_name << "!" << " Here is your Report Card:" << endl;
                found=true;
                file.close();
                return;
            }
        }
        cout<<"Enter your Name: ";
        getline(cin, s_name);
         cout<<"Enter your Number of courses: ";
        cin>>no_of_courses;
        cin.ignore(1000, '\n');
        cout<<"Enter your Semester: ";
        cin>>semester;
        cin.ignore(1000, '\n');
        for(int i=0;i<no_of_courses;i++){
        course c;
        c.input(i+1);
        courses.push_back(c);
        }
    }
    bool isFound(){
        return found;
    }
    double gpa_calculate(){
    double quality_point=0;
    int total_cr_hrs=0;
    double gpa;
        for(int i=0;i<courses.size();i++){
            double grade_point,percent;
           percent=(courses[i].get_obt_marks()*100)/courses[i].get_t_marks();
           grade_point=getGradePoint(percent);
           quality_point=quality_point+(courses[i].get_credit_hrs()*grade_point);
           total_cr_hrs=total_cr_hrs+courses[i].get_credit_hrs();
        }
         gpa=quality_point/total_cr_hrs;
          return gpa;
    }
    double getGradePoint(double percent){
    ifstream file("grading_scale.txt");
    int low, high;
    double gp;
     percent = floor(percent);
    if(!file.is_open()){
                return 0;
    }
    while(file >> low >> high >> gp){
        if(percent >= low && percent <= high){
            file.close();
            return gp;
        }
    }
    file.close();
    return 0.0; 
}
void writing_to_file(){
    double GPA=gpa_calculate();
    ofstream file("students.txt",ios::app);
    if(file.is_open()){
        file<<endl;
        file<<"Roll No: "<<roll_no<<endl;
        file<<"Name: "<<s_name<<endl;
        file<<"Number of courses: "<<no_of_courses<<endl;
        file<<"Semester: "<<semester<<endl;
        for(int i=0;i<courses.size();i++){
            file<<"Course "<<i+1<<" Name: "<<courses[i].get_course_name()<<endl;
            file<<"Credit Hours: "<<courses[i].get_credit_hrs()<<endl;
            file<<"Total Marks: "<<courses[i].get_t_marks()<<endl;
            file<<"Obtained Marks: "<<courses[i].get_obt_marks()<<endl;
        }
        file<<"GPA:"<<GPA<<endl;
        file<<endl;
        file.close();
    } else {
        cout<<"Unable to open file";
    }
}

void generate_report_card(double gpa){

    ifstream templateFile("template.html");
    string content = "";
    string line;
    while(getline(templateFile, line)){
        content += line + "\n";
    }
    templateFile.close();

    // & access deta ha function ko outer function ka variables ki
    //auto return type means compiler will figure out data type itself

    auto replace = [&](string placeholder, string value){ //function we created
        int pos = content.find(placeholder);
        if(pos != string::npos){
            content.replace(pos, placeholder.length(), value); //c++ built-in function
        }                //(pos,how manny chars,what to put)
        //pos= position and string::npos means no position not found
    };

   
    replace("STUDENT_NAME", s_name); //(placeholder,value)
    replace("STUDENT_ROLL", roll_no);
    replace("STUDENT_COURSES", to_string(no_of_courses));
    replace("STUDENT_SEMESTER", to_string(semester));
    replace("STUDENT_GPA", to_string(gpa).substr(0, 4));
    replace("TOTAL_CREDIT_HRS", to_string(getTotalCreditHrs()));

    string courseRows = ""; 
    //based on coursesize everything gets added to course row in proper html format
    //and then we call replace function everything gets added at once in the html file
    for(int i = 0; i < courses.size(); i++){
        double percent = (courses[i].get_obt_marks() * 100.0) / courses[i].get_t_marks();
        double gp = getGradePoint(percent);
        
        string grade;
        if(gp == 4.00) grade = "A";
        else if(gp == 3.66) grade = "A-";
        else if(gp == 3.33) grade = "B+";
        else if(gp == 3.00) grade = "B";
        else if(gp == 2.66) grade = "B-";
        else if(gp == 2.33) grade = "C+";
        else if(gp == 2.00) grade = "C";
        else if(gp == 1.66) grade = "C-";
        else if(gp == 1.33) grade = "D+";
        else if(gp == 1.00) grade = "D";
        else grade = "F";

        courseRows += "<tr>";
        courseRows += "<td>" + to_string(i+1) + "</td>";
        courseRows += "<td>" + courses[i].get_course_name() + "</td>";
        courseRows += "<td>" + to_string(courses[i].get_credit_hrs()) + "</td>";
        courseRows += "<td>" + to_string(courses[i].get_t_marks()) + "</td>";
        courseRows += "<td>" + to_string(courses[i].get_obt_marks()) + "</td>";
        courseRows += "<td>" + to_string((int)percent) + "%</td>";
        courseRows += "<td>" + grade + "</td>";
        courseRows += "<td>" + to_string(gp).substr(0,4) + "</td>";
        courseRows += "</tr>\n";
    }
    replace("COURSES_ROWS", courseRows);

    if(gpa >= 1.00)
        replace("STUDENT_RESULT", "PASS");
    else
        replace("STUDENT_RESULT", "FAIL");

    ofstream reportFile("report_card.html");
    reportFile << content;
    reportFile.close();

    system("start report_card.html");
}
int getTotalCreditHrs(){
    int total = 0;
    for(int i = 0; i < courses.size(); i++){
        total += courses[i].get_credit_hrs();
    }
    return total;
}

void load_from_file(){
    ifstream file("students.txt");
    string line;
    
    //  read line by line until we find our roll number
    while(getline(file, line)){
        if(line.find("Roll No: " + roll_no) != string::npos){
            
            // FOUND  Now read the next lines IN ORDER
            
            getline(file, line);                      // reads "Name: Amna Habib"
           s_name=line.substr(line.find(": ")+2);                   // cuts "Name: " → leaves "Amna Habib"
            
            getline(file, line);                       // reads "Number of courses: 2"
           no_of_courses = stoi(line.substr(line.find(": ")+2));     // cuts label → "2" → converts to int 2
            
            getline(file, line);                       // reads "Semester: 2"
            semester= stoi(line.substr(line.find(": ")+2));            // cuts label → "2" → converts to int 2
            
            // Now read each course 4 lines, repeated  how many no_of_courses times
            for(int i = 0; i < no_of_courses; i++){
                course c;
                
                getline(file, line);                                    // "Course 1 Name: OOP"
                string cname = line.substr(line.find(": ")+2);            // "OOP"
                //+2 because after we found (: ) we skip everything before it and 2 charcters are colon and 1 space

                getline(file, line);                                    // "Credit Hours: 3"
                int chrs = stoi(line.substr(line.find(": ")+2));          //  3
                
                getline(file, line);                                    // "Total Marks: 100"
                int tmarks = stoi(line.substr(line.find(": ")+2));        // 100
                
                getline(file, line);                                    // "Obtained Marks: 85"
                int omarks = stoi(line.substr(line.find(": ")+2));        // 85
                
                c.set_data(cname, chrs, tmarks, omarks);   // fill the course object
                courses.push_back(c);                       // add it to student's vector
            }
            
            break; 
        }
    }
    file.close();
}

};
int main(){
   student s;
   s.input();
   if(!s.isFound()){ //if record not found in our txt file
        double GPA=s.gpa_calculate();
    cout<<"Your GPA is: "<<GPA<<endl;
    s.writing_to_file();
      s.generate_report_card(GPA);
   }
   else {
        // if student data already in student.txt file
        s.load_from_file(); 
        double GPA = s.gpa_calculate(); // it calculated gpa from loaded data
        cout << "Your GPA is: " << GPA << endl;
        s.generate_report_card(GPA);
    }
   return 0;
}