import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: welcomePage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            welcomePage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(welcomePage.statusBarHoldEnabled)
            welcomePage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: loginManager

        onGetLoginHistoryResult: {
            var code = loginManager.getAppLoginStatus();
            if(code===0){
                pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
            }
            if(code===1){
                sessionListManager.getChatList();
                contactManager.getContactList();
                userProfileManager.getAccountInfo();
                groupManager.getGroupList();
                enterpriseManager.setFarOrg();
                orgManager.resetOrgList();
                chatManager.clearList();
                pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
            }
            if(code===2){
                if(userid===""||service===""){
                    pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
                }
                else{
                    loginManager.autoLogin(userid,service);
                }
            }
        }
        onLoginSucceeded: {
            console.log("onLoginSuccess !!!!")
            sessionListManager.getChatList();
            enterpriseManager.setFarOrg();
            orgManager.resetOrgList();
            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
        }
        onLoginFailed: {
            if(err === "帐号已经登录"){
                sessionListManager.getChatList();
                contactManager.getContactList();
                userProfileManager.getAccountInfo();
                groupManager.getGroupList();
                enterpriseManager.setFarOrg();
                orgManager.resetOrgList();
                chatManager.clearList();
                pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
                return;
            }
            gToast.requestToast("自動登錄失敗:"+err,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle{
            id:imagebackground
            anchors.fill: parent
            color:"white"
            Image{
                id:image1
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.top:parent.top
                anchors.topMargin: 80
                source: "qrc:/res/wlcomepage1.png"
            }
            Image{
                id:image2
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.top:image1.bottom
                anchors.topMargin: 85
                source: "qrc:/res/wlcomepage2.png"
            }
            AnimatedImage{
                id:image3
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.top:image2.bottom
                playing: true
                source: "qrc:/res/welcomepage3.gif"
            }
        }
    }
    Component.onCompleted: {
        //        loginManager.getLoginHistory();
        //        pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
    }
}
