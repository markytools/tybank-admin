QT += core
QT -= gui
QT += sql
QT += network

CONFIG += c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    atm.cpp \
    utils.cpp \
    statementmanager.cpp \
    bankdisplay.cpp \
    accountmanager.cpp \
    datahandler.cpp \
    mastercardapplication.cpp \
    sqldatabase.cpp \
    smtp.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    atm.h \
    utils.h \
    statementmanager.h \
    bankdisplay.h \
    accountmanager.h \
    datahandler.h \
    mastercardapplication.h \
    sqldatabase.h \
    smtp.h \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/smtpclient.h \
    src/smtpexports.h \
    src/SmtpMime


win32: LIBS += -L$$PWD/release/ -lSMTPEmail

INCLUDEPATH += $$PWD/release
DEPENDPATH += $$PWD/release
