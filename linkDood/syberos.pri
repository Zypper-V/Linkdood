QML_IMPORT_PATH = $$[QT_INSTALL_QML]

APP_DIR = /data/apps
APP_DATA = /data/data
INSTALL_DIR = $$APP_DIR/com.vrv.linkDood
DATA_DIR = $$APP_DATA/com.vrv.linkDood
LIB_DIR = /data/app-libs/com.vrv.linkDood

DEFINES += SOP_ID=\\\"com.vrv.linkDood\\\"
DEFINES += APP_DIR_ENVVAR=\\\"APPDIR_REGULAR\\\"
# Currently home screen sets the environment variable, so when run from
# elsewhere, use this work-around instead.
DEFINES += APP_DIR=\\\"$$APP_DIR\\\"
DEFINES += SOP_ID=\\\"com.vrv.linkDood\\\"
DEFINES += APP_DIR=\\\"$$APP_DIR\\\"

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application \
			   $$[QT_INSTALL_HEADERS]/../framework

