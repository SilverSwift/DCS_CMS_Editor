QT += \
    core \
    widgets \
    qml

HEADERS += \
    src/appfacade.h \
    src/model/a10cvalidator.h \
    src/model/cmsmodel.h \
    src/model/abstractvalidator.h \
    src/parsing/AbstractParser.h \
    src/parsing/a10cparser.h \
    src/parsing/mockparser.h \
    src/utils/numericutills.h

SOURCES += \
    src/appfacade.cpp \
    src/model/a10cvalidator.cpp \
    src/model/cmsmodel.cpp \
    src/main.cpp \
    src/parsing/a10cparser.cpp \
    src/parsing/mockparser.cpp \
    src/utils/numericutills.cpp

INCLUDEPATH += \
    $$PWD/src/model \
    $$PWD/src/parsing \
    $$PWD/src/utils

RESOURCES += \
        main.qrc
