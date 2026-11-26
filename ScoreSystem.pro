QT -= gui
CONFIG += console c++17
CONFIG -= app_bundle
TARGET = ScoreSystem

# 注意：test_manager.cpp 自带 main()，不要加进来，否则重复定义
SOURCES += \
    main.cpp \
    student.cpp \
    scoremanager.cpp

HEADERS += \
    student.h \
    scoremanager.h \
    utils.h \
    testcase.h

# 成员2的 GUI 提交后：改成 QT += widgets，去掉 console，
# 把 mainwindow.* 和 fileio.* 加进 SOURCES / HEADERS
