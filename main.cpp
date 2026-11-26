// 成员3：项目入口（目前是控制台版本，成员2的 GUI 提交后再切换）
#include "scoremanager.h"
#include "utils.h"
#include "testcase.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);   // 避免 Windows 控制台中文乱码
#endif

    int failed = TestCase::runAll();

    // 演示：打印一份排好序的成绩表（截图放报告里）
    ScoreManager mgr;
    mgr.addStudent(Student("2023001", "张三", 60, 70, 80, 90));
    mgr.addStudent(Student("2023002", "李四", 85, 85, 85, 85));
    mgr.addStudent(Student("2023003", "王五", 90, 60, 90, 60));
    mgr.sortByAverage();
    std::cout << "\n===== 成绩表 =====\n";
    Utils::printTable(mgr.getAll());

    return failed == 0 ? 0 : 1;
}
