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

    Connections {
        target: gScreenInfo

        onMinimizedChanged: {
            loginManager.setWindowFocus(!gScreenInfo.minimized)
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

    Component.onCompleted: {
        var code = loginManager.loginStatus;
        console.log("sfdsgsdfgsfdg:"+code);
        if(code === 1){
            sessionListManager.getChatList();
            contactManager.getContactList();
            userProfileManager.getAccountInfo();
            groupManager.getGroupList();
            enterpriseManager.setFarOrg();
            orgManager.resetOrgList();
            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
        }else{
            pageStack.replace(Qt.resolvedUrl("CDoodLoginPage.qml"), "", true);
        }
    }
    Connections{
        target: loginManager
        onServiceRestart:{
            pageStack.replace(Qt.resolvedUrl("CDoodLoginPage.qml"), "", true);
        }
    }
}
