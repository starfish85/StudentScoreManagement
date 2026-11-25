#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include "student.h"
#include <vector>
#include <string>

// 所有业务都在这，成员2/3 调这几个方法就行
class ScoreManager {
public:
    // 【增】加学生，返回 true 成功，false 失败（学号重复或参数非法）
    bool addStudent(const Student& s);
    // 【删】按学号删，返回 true 找到删了，false 没找到
    bool deleteStudent(const std::string& id);
    // 【改】按学号改4科成绩，自动更新平均分；返回 true 改了，false 没找到
    bool modifyStudent(const std::string& id,
                       double m, double e, double a, double o);
    // 【查】按学号找，返回引用（能改里面的内容）；找不到抛异常
    //   调用示例：
    //   auto& s = mgr.searchById("2023001");
    //   (找不到时会抛 std::runtime_error，成员2可以 try/catch 弹窗)
    Student& searchById(const std::string& id);
    // 【查】辅助方法：按学号找，返回指针；找不到返回 nullptr
    //   （给成员3统计时安全遍历用）
    Student* findById(const std::string& id);
    // 【排】按平均分降序排，同时填 rank（并列也处理好）
    void sortByAverage();

    // 【给别人遍历用】返回所有学生的列表引用（成员2渲染表格、成员3统计都用这个）
    const std::vector<Student>& getAll() const { return list; }
    // 学生总数
    int size() const { return (int)list.size(); }
    // 清空（成员2启动加载前先清）
    void clear() { list.clear(); }
    // 学号是否存在（成员2/3也可能要单独查重）
    bool exists(const std::string& id) const;

private:
    std::vector<Student> list;  // 就存值，不用指针，大一能看懂
};

#endif
