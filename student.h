#ifndef STUDENT_H
#define STUDENT_H
#include <string>

// 头文件不放 using namespace std; —— 避免污染别人的命名空间

class Student {
public:
    std::string id;     // 学号（用 string，0 开头不会被吃掉）
    std::string name;   // 姓名
    double math;        // 高数
    double english;     // 英语
    double algo;        // 算法
    double os;          // 操作系统
    double average;     // 平均分（自动算，不要手动改）
    int rank;           // 名次（排序后填，初始0）

    Student();
    Student(std::string _id, std::string _name,
            double m, double e, double a, double o);

    // 每次改成绩后必须调这个重算平均分
    void updateAverage();
};

#endif
