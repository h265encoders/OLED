#-------------------------------------------------
#
# Project created by QtCreator 2019-09-18T14:53:36
#
#-------------------------------------------------

QT       += core gui  network testlib  websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = OLED
TEMPLATE = app
chip = HI3521D
include(../../LinkLib/Link.pri)
LIBS +=-lLinkUI

SOURCES += main.cpp\
    jcon/json_rpc_client.cpp \
    jcon/json_rpc_debug_logger.cpp \
    jcon/json_rpc_endpoint.cpp \
    jcon/json_rpc_error.cpp \
    jcon/json_rpc_file_logger.cpp \
    jcon/json_rpc_logger.cpp \
    jcon/json_rpc_request.cpp \
    jcon/json_rpc_server.cpp \
    jcon/json_rpc_success.cpp \
    jcon/json_rpc_tcp_client.cpp \
    jcon/json_rpc_tcp_server.cpp \
    jcon/json_rpc_tcp_socket.cpp \
    jcon/json_rpc_websocket_client.cpp \
    jcon/json_rpc_websocket_server.cpp \
    jcon/json_rpc_websocket.cpp \
    jcon/string_util.cpp \
    rpc.cpp \
    mods/cpu.cpp \
    mods/temp.cpp \
    mods/aud.cpp \
    mods/br.cpp \
    mods/mod.cpp \
    owns/gpio.cpp \
    view.cpp \
    mods/ipadr.cpp \
    mods/disk.cpp \
    mods/mem.cpp \
    mods/rec.cpp \
    mods/input.cpp \
    icon.cpp \
    mods/sign.cpp \
    owns/own.cpp \
    owns/rotate.cpp

HEADERS  += jcon/jcon_assert.h \
    jcon/jcon.h \
    jcon/json_rpc_client.h \
    jcon/json_rpc_debug_logger.h \
    jcon/json_rpc_endpoint.h \
    jcon/json_rpc_error.h \
    jcon/json_rpc_file_logger.h \
    jcon/json_rpc_logger.h \
    jcon/json_rpc_request.h \
    jcon/json_rpc_result.h \
    jcon/json_rpc_server.h \
    jcon/json_rpc_socket.h \
    jcon/json_rpc_success.h \
    jcon/json_rpc_tcp_client.h \
    jcon/json_rpc_tcp_server.h \
    jcon/json_rpc_tcp_socket.h \
    jcon/json_rpc_websocket_client.h \
    jcon/json_rpc_websocket_server.h \
    jcon/json_rpc_websocket.h \
    jcon/string_util.h \
    object.h \
    rpc.h \
    mods/cpu.h \
    mods/temp.h \
    mods/aud.h \
    mods/br.h \
    mods/mod.h \
    owns/gpio.h \
    view.h \
    mods/ipadr.h \
    mods/disk.h \
    mods/mem.h \
    mods/rec.h \
    mods/input.h \
    icon.h \
    mods/sign.h \
    owns/own.h \
    owns/rotate.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
