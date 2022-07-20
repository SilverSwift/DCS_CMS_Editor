QT += \
    core \
    qml\
    quick \
    quickcontrols2 \
    svg \
    widgets \
    xml

HEADERS += \
    src/appfacade.h \
    src/model/a10cvalidator.h \
    src/model/av8bvalidator.h \
    src/model/cmsmodel.h \
    src/model/abstractvalidator.h \
    src/model/f16cvalidator.h \
    src/model/fa18cvalidator.h \
    src/model/m2000cvalidator.h \
    src/parsing/a10cparser.h \
    src/parsing/abstractparser.h \
    src/parsing/av8bparser.h \
    src/parsing/baseluaparser.h \
    src/parsing/f16cparser.h \
    src/parsing/fa18cparcer.h \
    src/parsing/m2000cparser.h \
    src/parsing/mockparser.h \
    src/parsing/parsing_types.h \
    src/utils/gamefilesmanager.h \
    src/utils/installationinfo.h \
    src/utils/numericutills.h

SOURCES += \
    src/appfacade.cpp \
    src/model/a10cvalidator.cpp \
    src/model/av8bvalidator.cpp \
    src/model/cmsmodel.cpp \
    src/main.cpp \
    src/model/f16cvalidator.cpp \
    src/model/fa18cvalidator.cpp \
    src/model/m2000cvalidator.cpp \
    src/parsing/a10cparser.cpp \
    src/parsing/av8bparser.cpp \
    src/parsing/baseluaparser.cpp \
    src/parsing/f16cparser.cpp \
    src/parsing/fa18cparcer.cpp \
    src/parsing/m2000cparser.cpp \
    src/parsing/mockparser.cpp \
    src/utils/gamefilesmanager.cpp \
    src/utils/installationinfo.cpp \
    src/utils/numericutills.cpp

INCLUDEPATH += \
    $$PWD/src/model \
    $$PWD/src/parsing \
    $$PWD/src/utils

RESOURCES += \
        main.qrc

RC_ICONS = img/icon.ico
