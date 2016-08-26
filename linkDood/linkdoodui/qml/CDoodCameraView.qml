import QtQuick 2.0

import com.syberos.multimedia.camera 1.0  // 导入插件库

CameraPlugin {
    id: plugin

    property string mySessionId

    outputPath: chatManager.cameraFilePath()

    enablePostPreview: true  //必要设置
    enableCut: false //必要设置
    apertureShape: false
}
