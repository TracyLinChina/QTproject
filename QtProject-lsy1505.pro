TEMPLATE += app

SOURCES += main.cpp \
           MainWindow.cpp \
           Cline.cpp \
           Shape.cpp  \
           mod.cpp  \
           circle.cpp \
           polygon.cpp \
           Angle.cpp  \
           rectangle.cpp \
           DockWin.cpp \
           ModWidth.cpp \
           scale.cpp \
           scaleInfo.cpp \
           ScaleSave.cpp \
           CSinfo.cpp

HEADERS += MainWindow.h \
           Cline.h \
           Shape.h  \
           mod.h  \
           circle.h  \
           rectangle.h \
           polygon.h   \
           Angle.h \
           DockWin.h \
           ModWidth.h \
           scale.h \
           scaleInfo.h \
           ScaleSave.h \
           CSinfo.h

FORMS += MainWindow.ui \
         mod.ui  \
         DockWin.ui \
         ModWidth.ui \
         scaleInfo.ui \
         ScaleSave.ui

RESOURCES += rec.qrc \
             DockRes.qrc

