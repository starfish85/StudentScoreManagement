#include "student.h"
using namespace std;  // using 只放 .cpp 里

// 无参构造：全设为0/空
Student::Student() {
    id = ""; name = "";
    math = english = algo = os = 0.0;
    average = 0.0; rank = 0;
}

// 全参构造：赋值 + 自动算平均分
Student::Student(std::string _id, std::string _name,
                 double m, double e, double a, double o) {
    id = _id; name = _name;
    math = m; english = e; algo = a; os = o;
    updateAverage();  // 构造时自动算平均分
    rank = 0;
}

// 平均分公式：(高数+英语+算法+操作系统)/4
void Student::updateAverage() {
    average = (math + english + algo + os) / 4.0;
}
