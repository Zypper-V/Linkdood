import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: takePhotoPage

    signal showTakePhoto

    onStatusChanged: {
    }
    contentAreaItem:Item {
        anchors.fill :parent
    }
    onShowTakePhoto: {
        var component= pageStack.push(Qt.resolvedUrl("CDoodCameraView.qml"),{ rootWindow: mainPageView});
        component.imageConfirmed.connect(cameraSavePic)
    }

    function cameraSavePic (filePath, is_original) {
        chatManager.sendPictrue(filePath,true);
        console.log("filePath:"+filePath)
        pageStack.pop();
    }
}
