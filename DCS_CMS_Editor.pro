QT += \
    core \
    widgets \
    qml\
    quick

HEADERS += \
    src/appfacade.h \
    src/model/a10cvalidator.h \
    src/model/cmsmodel.h \
    src/model/abstractvalidator.h \
    src/model/fa18cvalidator.h \
    src/parsing/a10cparser.h \
    src/parsing/abstractparser.h \
    src/parsing/fa18cparcer.h \
    src/parsing/mockparser.h \
    src/utils/gamefilesmanager.h \
    src/utils/installationinfo.h \
    src/utils/numericutills.h

SOURCES += \
    src/appfacade.cpp \
    src/model/a10cvalidator.cpp \
    src/model/cmsmodel.cpp \
    src/main.cpp \
    src/model/fa18cvalidator.cpp \
    src/parsing/a10cparser.cpp \
    src/parsing/fa18cparcer.cpp \
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
