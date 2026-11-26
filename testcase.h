#ifndef TESTCASE_H
#define TESTCASE_H
// 成员3：批量边界测试（需要 C++17）
#include "scoremanager.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

namespace TestCase {

inline int g_pass = 0;
inline int g_fail = 0;

inline void check(bool cond, const std::string& desc) {
    if (cond) { ++g_pass; std::cout << "  [PASS] " << desc << "\n"; }
    else      { ++g_fail; std::cout << "  [FAIL] " << desc << "\n"; }
}

// 造 3 个基础学生
inline void fill(ScoreManager& m) {
    m.addStudent(Student("2023001", "张三", 60, 70, 80, 90));
    m.addStudent(Student("2023002", "李四", 85, 85, 85, 85));
    m.addStudent(Student("2023003", "王五", 90, 60, 90, 60));
}

inline void testDuplicateId() {
    std::cout << "\n--- 1. 添加重复学号 ---\n";
    ScoreManager m; fill(m);
    check(!m.addStudent(Student("2023001", "重复号", 1, 1, 1, 1)), "重复学号被拒绝");
    check(m.size() == 3, "人数仍为 3");
    check(m.exists("2023001") && !m.exists("9999"), "exists() 判断正确");
}

inline void testDeleteNotExist() {
    std::cout << "\n--- 2. 删除不存在的学号 ---\n";
    ScoreManager m; fill(m);
    check(!m.deleteStudent("9999"), "删除不存在学号返回 false");
    check(m.size() == 3, "人数不变");
    check(m.deleteStudent("2023003") && m.size() == 2, "删除存在学号成功");
}

inline void testModify() {
    std::cout << "\n--- 3. 修改成绩 ---\n";
    ScoreManager m; fill(m);
    check(!m.modifyStudent("9999", 1, 1, 1, 1), "修改不存在学号返回 false");
    check(m.modifyStudent("2023001", 100, 100, 100, 100), "修改存在学号成功");
    Student* s = m.findById("2023001");
    check(s != nullptr && std::fabs(s->average - 100.0) < 1e-9, "修改后平均分自动重算为 100");
}

inline void testSearch() {
    std::cout << "\n--- 4. 查询 ---\n";
    ScoreManager m; fill(m);
    check(m.findById("9999") == nullptr, "findById 找不到返回 nullptr");
    bool thrown = false;
    try { m.searchById("9999"); } catch (const std::runtime_error&) { thrown = true; }
    check(thrown, "searchById 找不到抛 runtime_error");
    bool found = false;
    try { found = (m.searchById("2023002").name == "李四"); } catch (...) {}
    check(found, "searchById 找到李四");
}

inline void testInvalidScore() {
    std::cout << "\n--- 5. 非法分数（负分 / 大于 100）---\n";
    using Utils::ErrorCode;
    check(Utils::validateInput("1", "甲", -1, 50, 50, 50) == ErrorCode::SCORE_OUT_OF_RANGE, "负分被 Utils 拦截");
    check(Utils::validateInput("1", "甲", 50, 100.5, 50, 50) == ErrorCode::SCORE_OUT_OF_RANGE, "大于 100 被 Utils 拦截");
    check(Utils::validateInput("1", "甲", 0, 100, 0, 100) == ErrorCode::OK, "边界值 0 和 100 合法");
    check(Utils::validateInput("  ", "甲", 50, 50, 50, 50) == ErrorCode::EMPTY_ID, "学号为空被拦截");
    check(Utils::validateInput("1", "", 50, 50, 50, 50) == ErrorCode::EMPTY_NAME, "姓名为空被拦截");

    // 探测：底层 ScoreManager 自己拦不拦？（只报告，不判失败）
    ScoreManager m;
    bool neg = m.addStudent(Student("X1", "负分", -5, 70, 80, 90));
    bool big = m.addStudent(Student("X2", "超分", 101, 70, 80, 90));
    std::cout << "  [探测] 底层 addStudent 对负分：" << (neg ? "接受" : "拒绝")
              << "；对 >100：" << (big ? "接受" : "拒绝") << "\n";
}

inline void testRankTies() {
    std::cout << "\n--- 6. 排序与并列名次 ---\n";
    ScoreManager m;
    m.addStudent(Student("A", "甲", 70, 70, 70, 70));
    m.addStudent(Student("B", "乙", 85, 85, 85, 85));
    m.addStudent(Student("C", "丙", 100, 100, 100, 100));
    m.addStudent(Student("D", "丁", 85, 85, 85, 85));
    m.addStudent(Student("E", "戊", 85, 85, 85, 85));
    m.sortByAverage();
    const auto& v = m.getAll();
    bool desc = true;
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1].average < v[i].average) desc = false;
    check(desc, "按平均分降序");
    check(v[0].rank == 1, "最高分名次 1");
    check(v[1].rank == 2 && v[2].rank == 2 && v[3].rank == 2, "同分三人并列名次 2");
    check(v[4].rank == 5, "并列之后下一名次为 5（当前位置+1）");
}

inline void testEmptyAndClear() {
    std::cout << "\n--- 7. 空列表 / clear ---\n";
    ScoreManager m;
    m.sortByAverage();
    check(m.size() == 0, "空列表排序不崩溃");
    fill(m); m.clear();
    check(m.size() == 0, "clear 后人数为 0");
}

// 跑全部测试，返回失败数
inline int runAll() {
    g_pass = g_fail = 0;
    testDuplicateId();
    testDeleteNotExist();
    testModify();
    testSearch();
    testInvalidScore();
    testRankTies();
    testEmptyAndClear();
    std::cout << "\n===== 测试结果：通过 " << g_pass << "，失败 " << g_fail << " =====\n";
    return g_fail;
}

} // namespace TestCase

#endif
