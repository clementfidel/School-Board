QT += widgets \
      sql \
      network \
      core \
      gui

SOURCES += \
    main.cpp \
    fenconnexion.cpp \
    fenadmin.cpp \
    fenprof.cpp \
    feneleve.cpp \
    fenajuser.cpp \
    fensuppuser.cpp \
    fenmodifuser.cpp \
    fenajcours.cpp \
    fensuppcours.cpp \
    fenmodifcours.cpp \
    fenmodifclasses.cpp \
    fenmodifsalle.cpp \
    fenmodifmatiere.cpp \
    smtp.cpp \
    occupation.cpp \
    bulletin.cpp

HEADERS += \
    fenconnexion.h \
    fenadmin.h \
    fenprof.h \
    feneleve.h \
    smtp.h \



LIBS += -LC:\wamp64\bin\mysql\mysql5.7.23\lib -llibmysql

RESOURCES += \
    fenconnexion.qrc

FORMS += \
    fenconnexion.ui \
    fenprof.ui \
    feneleve.ui \
    fenadmin.ui \


TARGET = smtp
TEMPLATE = app


