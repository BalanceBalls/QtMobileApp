QT += quick network

CONFIG += c++11

#LIBS += -LC:/OpenSSL-Win32/lib/MinGW -llibcrypto-1_1
#LIBS += -LC:/OpenSSL-Win32/lib/MinGW -llibssl-1_1
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    json_loader.cpp \
    pairlistmodel.cpp \
    clientforserver.cpp \
    serverdatamodel.cpp




#LIBS +=  -L"$$_PRO_FILE_PWD_" -llibeay32
#LIBS +=  -L"$$_PRO_FILE_PWD_" -lssleay32
RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    json_loader.h \
    pairlistmodel.h \
    clientforserver.h \
    serverdatamodel.h

DISTFILES +=



