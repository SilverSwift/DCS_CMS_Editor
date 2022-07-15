QT += \
    core \
    widgets \
    qml

HEADERS += \
    src/appobject.h \
    src/cmsmodel.h \
    src/parsing/AbstractParser.h \
    src/parsing/a10cparser.h \
    src/parsing/mockparser.h \
    src/utils/numericutills.h

SOURCES += \
    src/appobject.cpp \
    src/cmsmodel.cpp \
    src/main.cpp \
    src/parsing/a10cparser.cpp \
    src/parsing/mockparser.cpp \
    src/utils/numericutills.cpp

INCLUDEPATH += \
    $$PWD/src/utils \
    $$PWD/src/parsing

RESOURCES += \
        main.qrc
