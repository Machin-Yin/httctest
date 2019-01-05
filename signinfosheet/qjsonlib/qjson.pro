TEMPLATE     = lib
DEPENDPATH  += . 
INCLUDEPATH += . 

# Input
SOURCES += parser.cpp qobjecthelper.cpp json_scanner.cpp json_parser.cc 
SOURCES += parserrunnable.cpp serializer.cpp serializerrunnable.cpp
HEADERS += parser.h qobjecthelper.h serializer.h
HEADERS += serializerrunnable.h qjson_export.h  parserrunnable.h 
DEFINES += QJSON_MAKEDLL

#QMAKE_POST_LINK = cp -ap libqjson.so* /opt/softmanager/lib/ ;
QMAKE_POST_LINK += cp -ap libqjson.so* ../../../output/lib/
#QMAKE_CLEAN = libqjson.so* /opt/softmanager/lib/libqjson.so*
QMAKE_CLEAN += ../../../output/lib/libqjson.so* 

