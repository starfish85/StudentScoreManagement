#ifndef UTILS_H
#define UTILS_H
// 成员3：通用工具类（头文件实现，不需要 utils.cpp）
#include "student.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

namespace Utils {

// 统一错误码（成员2的界面弹窗也可以直接用）
enum class ErrorCode {
    OK = 0,
    EMPTY_ID = 1,
    EMPTY_NAME = 2,
    SCORE_OUT_OF_RANGE = 3,
    DUPLICATE_ID = 4,
    NOT_FOUND = 5
};

inline std::string errorMessage(ErrorCode c) {
    switch (c) {
    case ErrorCode::OK:                 return "成功";
    case ErrorCode::EMPTY_ID:           return "学号不能为空";
    case ErrorCode::EMPTY_NAME:         return "姓名不能为空";
    case ErrorCode::SCORE_OUT_OF_RANGE: return "分数必须在 0~100 之间";
    case ErrorCode::DUPLICATE_ID:       return "学号已存在";
    case ErrorCode::NOT_FOUND:          return "未找到该学号";
    }
    return "未知错误";
}

// 去掉首尾空白
inline std::string trim(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    return s.substr(b, e - b);
}

// 分数是否合法（NaN 也会返回 false）
inline bool isValidScore(double s) { return s >= 0.0 && s <= 100.0; }

// 一次性校验录入信息，返回第一个发现的错误
inline ErrorCode validateInput(const std::string& id, const std::string& name,
                               double m, double e, double a, double o) {
    if (trim(id).empty())   return ErrorCode::EMPTY_ID;
    if (trim(name).empty()) return ErrorCode::EMPTY_NAME;
    if (!isValidScore(m) || !isValidScore(e) ||
        !isValidScore(a) || !isValidScore(o))
        return ErrorCode::SCORE_OUT_OF_RANGE;
    return ErrorCode::OK;
}

// 分数格式化：保留 1 位小数
inline std::string formatScore(double v) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << v;
    return os.str();
}

// 控制台打印成绩表（用 tab 分隔，中文不会错位）
inline void printTable(const std::vector<Student>& list) {
    std::cout << "学号\t姓名\t高数\t英语\t算法\t操作系统\t平均分\t名次\n";
    for (const auto& s : list) {
        std::cout << s.id << '\t' << s.name << '\t'
                  << formatScore(s.math) << '\t' << formatScore(s.english) << '\t'
                  << formatScore(s.algo) << '\t' << formatScore(s.os) << "\t\t"
                  << formatScore(s.average) << '\t' << s.rank << '\n';
    }
}

} // namespace Utils

#endif
