#include "scoremanager.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>  // runtime_error
using namespace std;

// ⚠️ 必须加 static —— 限制这个比较函数只在本 cpp 可见
// 不然 Qt Creator 多文件链接时会报 multiple definition!
static bool cmpAverageDesc(const Student& a, const Student& b) {
    return a.average > b.average;
}

// 先写个查重辅助（增删改都要用）
bool ScoreManager::exists(const std::string& id) const {
    for (auto& s : list) {
        if (s.id == id) return true;
    }
    return false;
}

// 【增】先查重，没有就 push_back
bool ScoreManager::addStudent(const Student& s) {
    if (s.id.empty()) return false;   // 学号不能为空
    if (exists(s.id)) return false;   // 学号重复，拒绝
    list.push_back(s);                 // vector 存值，大一能看懂
    return true;
}

// 【删】遍历找学号，找到就 erase
bool ScoreManager::deleteStudent(const std::string& id) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->id == id) {
            list.erase(it);  // 值类型直接 erase，不用 delete
            return true;
        }
    }
    return false;
}

// 【改】先找到（遍历），然后改成绩，然后重算平均分
bool ScoreManager::modifyStudent(const std::string& id,
                                 double m, double e, double a, double o) {
    for (auto& stu : list) {  // 注意是引用 &，要改 stu 的内容
        if (stu.id == id) {
            stu.math = m; stu.english = e; stu.algo = a; stu.os = o;
            stu.updateAverage();  // 改完必须算平均分！
            return true;
        }
    }
    return false;
}

// 【查】按学号找，返回指针；找不到返回 nullptr（安全版，供成员3遍历）
Student* ScoreManager::findById(const std::string& id) {
    for (auto& stu : list) {
        if (stu.id == id) return &stu;
    }
    return nullptr;
}

// 【查】按学号找，返回引用；找不到抛异常（方便成员2直接用）
Student& ScoreManager::searchById(const std::string& id) {
    for (auto& stu : list) {
        if (stu.id == id) return stu;
    }
    // 找不到就抛异常，调用方用 try/catch 处理
    throw std::runtime_error("学号 " + id + " 不存在");
}

// 【排】排序 + 并列名次（两步走）
void ScoreManager::sortByAverage() {
    if (list.empty()) return;

    // 第一步：排序（降序，平均分高的排前面）
    sort(list.begin(), list.end(), cmpAverageDesc);

    // 第二步：填名次
    // 并列逻辑：和前一人同分就用前一人的名次，否则 = 当前位置下标+1
    list[0].rank = 1;  // 第一名肯定是1
    for (size_t i = 1; i < list.size(); i++) {
        // fabs 取绝对值，1e-6 是 double 比较允许的误差
        if (fabs(list[i].average - list[i-1].average) < 1e-6) {
            list[i].rank = list[i-1].rank;   // 同分，名次和前一个一样
        } else {
            list[i].rank = (int)i + 1;       // 不同分，名次=当前位置+1
        }
    }
}
