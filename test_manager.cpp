// 编译命令（Qt Creator）：新建控制台工程，把 student.cpp / scoremanager.cpp / test_manager.cpp 都加进去直接跑
// 编译命令（g++）：g++ student.cpp scoremanager.cpp test_manager.cpp -std=c++17 -o test.exe
#include "scoremanager.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    ScoreManager mgr;

    // —— 1. 添加测试 ——
    cout << "=== 添加测试 ===" << endl;
    bool b1 = mgr.addStudent(Student("2023001","张三",60,70,80,90));
    bool b2 = mgr.addStudent(Student("2023002","李四",85,85,85,85));
    bool b3 = mgr.addStudent(Student("2023003","王五",90,60,90,60));
    cout << "加3人：" << (b1&&b2&&b3 ? "成功" : "失败") << endl;

    // 重复学号测试
    bool bDup = mgr.addStudent(Student("2023001","重复号",1,1,1,1));
    cout << "重复学号添加：" << (bDup ? "（错！没拦住）" : "（对！拦住了）") << endl;
    cout << "当前人数：" << mgr.size() << endl;  // 应该是3

    // —— 2. 修改测试 ——
    cout << "\n=== 修改测试 ===" << endl;
    mgr.modifyStudent("2023001", 100,100,100,100);  // 把张三改成全满分
    Student* zs = mgr.findById("2023001");
    cout << "修改后张三平均分：" << zs->average << "（应该100）" << endl;

    // —— 3. 删除测试 ——
    cout << "\n=== 删除测试 ===" << endl;
    bool bDel = mgr.deleteStudent("2023003");
    cout << "删王五：" << (bDel ? "成功" : "失败") << endl;
    cout << "当前人数：" << mgr.size() << endl;  // 应该是2

    // —— 4. searchById 引用版测试 ——
    cout << "\n=== searchById 测试 ===" << endl;
    try {
        auto& s = mgr.searchById("2023002");
        cout << "找到李四：" << s.name << " 平均分=" << s.average << endl;
    } catch (const runtime_error& e) {
        cout << "异常：" << e.what() << endl;
    }
    // 找不到测试
    try {
        auto& s = mgr.searchById("999999");
        cout << "（不该执行到这里）" << endl;
    } catch (const runtime_error& e) {
        cout << "找不到学号正常抛异常：" << e.what() << endl;
    }

    // —— 5. 排序+并列名次测试 ——
    cout << "\n=== 排序+名次测试 ===" << endl;
    // 加两人和李四同分（85*4=85分），测并列
    mgr.addStudent(Student("2023004","赵六",85,85,85,85));
    mgr.addStudent(Student("2023005","钱七",85,85,85,85));
    mgr.sortByAverage();

    const vector<Student>& list = mgr.getAll();
    cout << "排序后列表：" << endl;
    for (auto s : list) {
        cout << "  " << s.id << " " << s.name
             << " 平均分：" << s.average
             << " 名次：" << s.rank << endl;
    }
    // 预期：张三(100,rk1) → 李四/赵六/钱七(85,rk2) 共4人

    cout << "\n测试完成！" << endl;
    return 0;
}
