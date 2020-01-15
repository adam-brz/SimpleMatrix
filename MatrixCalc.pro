#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T18:09:07
#
#-------------------------------------------------

QT       += core

TARGET = MatrixCalc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

HEADERS += \
    matrix.h \
    Tests/catch.hpp \
    Tests/debugtoolbox.h \
    matrixexception.h \
    vector.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

#Tests

contains(DEFINES, RUN_TEST) {
    SOURCES +=  Tests/testmain.cpp \
        Tests/catch_test.cpp \
        Tests/Matrix/determinant_test.cpp \
        Tests/Matrix/invert_test.cpp \
        Tests/Matrix/transpose_test.cpp \
        Tests/Matrix/add_test.cpp \
        Tests/Matrix/subtract_test.cpp \
        Tests/Matrix/multiply_test.cpp \
        Tests/Matrix/reverse_elements_test.cpp \
        Tests/Matrix/rotate_test.cpp \
        Tests/Matrix/compare_test.cpp \
        Tests/Matrix/assign_test.cpp  \
        Tests/Matrix/matrix_creation_test.cpp \
        Tests/Vector/v_add_test.cpp \
        Tests/Vector/v_assign_test.cpp \
        Tests/Vector/v_compare_test.cpp \
        Tests/Vector/v_creation_test.cpp \
        Tests/Vector/v_get_test.cpp \
        Tests/Vector/v_is_column_test.cpp \
        Tests/Vector/v_size_test.cpp\
        Tests/Vector/v_test_from_matrix.cpp
}

else:contains(DEFINES, RUN_TIME_TEST) {
    SOURCES += Tests/timetests.cpp
}

else {
    SOURCES += main.cpp
}

SOURCES += \
    Tests/Vector/v_abs_test.cpp \
    Tests/Vector/v_make_negative.cpp \
    Tests/Vector/v_mul_test.cpp \
    Tests/Vector/v_sub_test.cpp
