VERSION = 1.0
TEMPLATE = subdirs
CONFIG += debug ordered

#SUBDIRS += core qt-qml meego-mpl
SUBDIRS += core qt-qml

system(pkg-config --exists meego-panel) {
 SUBDIRS += meego-mpl
} 