import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPageStackWindow {
    id: mainPageView
    inputFactor: 0
    keyHandle:false

    onBackKey:{
        if(clearFocus()){
            event.accepted =true
            return
        }

        if(mainPageView.pageStack.depth > 1) {
            mainPageView.pageStack.pop();
        } else {
            winHide()
        }
    }

    Keys.onReleased:{
        if (event.key === Qt.Key_Home) {
            winHide();
        }
    }

    initialPage:CPage{
        id: startPage
        anchors.fill: parent
        orientationLock: CPageOrientation.LockPortrait

        onStateChanged: {
            if (status == CPageStatus.WillShow) {
                gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE",true)
                gScreenInfo.setWindowProperty("STATUSBAR_STYLE","transBlack")
            } else if (status == CPageStatus.Show) {
            }
        }
    }
}
