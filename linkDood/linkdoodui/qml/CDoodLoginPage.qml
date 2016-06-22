import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: loginPage

    property string  server
    property string  name
    property string  password

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            loginPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(loginPage.statusBarHoldEnabled)
            loginPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    Connections {
        target: loginManager

//        onInputRootTabView: {
//            console.log("onInputRootTabView !!!!")
//            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
//        }

        onLoginSucceeded: {
            console.log("onLoginSuccess !!!!")
            loadingDialog.hide();
            sessionListManager.getChatList();
            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);

//            var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodChatPage.qml"),"CDoodChatPage");
        }
        onLoginResultObserver:{
            console.log("onLoginResultObserver !!!!");
            loginManager.setLoginInfo(2,userID,srvUsr.text,"");
        }

        onLoginFailed: {
            console.log("onLoginFailed !!!!")
            loadingDialog.hide();
            gToast.requestToast(err,"","");
        }
    }

    contentAreaItem: Item {
        anchors.fill :parent
        Rectangle {
            id: loginBackground
            anchors.fill: parent
            color: "#f2f2f2"
        }

        Flickable{
            id: filckableInput
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            contentHeight: parent.height

            Connections {
                target: gInputContext
                onSoftwareInputPanelVisibleChanged: {
                    if(gInputContext.softwareInputPanelVisible) {
                        filckableInput.contentHeight = filckableInput.parent.height + 200
                    } else {
                        filckableInput.contentHeight = filckableInput.parent.height
                    }
                }
            }

            Rectangle{
                id:titleBackground

                anchors.top: parent.top
                anchors.left: parent.left

                width:parent.width
                height: 110
                color:"#1c1b21"
                Text{
                    id:titleText

                    anchors.centerIn: parent

                    text:qsTr("登录-天工圆圆")
                    color:"white"
                    font.pixelSize: 36
                }
            }

            Item {
                id: logoInlogonImage

                anchors.top: titleBackground.bottom
                anchors.horizontalCenter: parent.horizontalCenter

                width: parent.width
                height: 310

                Image {
                    id: logoImage

                    anchors.centerIn: parent
                    width: 128
                    height: 128
                    z: 10

                    smooth: true
                    asynchronous: true
                    sourceSize: Qt.size(128, 128)
                    source: "qrc:/res/logo.png"

                    onStatusChanged: {
                        if (logoImage.status === Image.Error || logoImage.status === Image.Null) {
                            logoImage.source = "qrc:/res/logo.png"
                        }
                    }
                }
            }

            Rectangle {
                id: inputBackGround

                anchors.top: logoInlogonImage.bottom
                anchors.bottom: passWordEdit.bottom
                width: parent.width
                color: "#ffffff"
            }

            Item {
                id: moreBtnRoot
                anchors.top: logoInlogonImage.bottom
                anchors.topMargin: 28
                anchors.right: parent.right

                height: 120
                visible: false
                width:  91

                Image {
                    id: moreBtn
                    anchors.centerIn: parent
                    smooth: true
                    sourceSize: Qt.size(31, 20)
                    source: "qrc:/res/more.png"
                    asynchronous: true
                }

                Behavior on opacity {
                    NumberAnimation { duration: 200 }
                }

                MouseArea {
                    anchors.fill: parent

                    onPressed: {
                        moreBtnRoot.opacity = 0.3
                    }

                    onReleased: {
                        moreBtnRoot.opacity = 1

                        if(loginPage.state !== "show")
                            loginPage.state = "show"
                        else
                            loginPage.state = "hidden"
                    }

                    onCanceled: {
                        moreBtnRoot.opacity = 1
                    }
                }
            }

            CLine {
                width: parent.width
                z: parent.z+2

                anchors.bottom: srvLineEdit.bottom
            }

            Rectangle{
                anchors.top: logoInlogonImage.bottom
                anchors.left: parent.left

                height: 85
                z: moreBtnRoot.z - 5
                width: parent.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        srvLineEdit.focus = true;
                    }
                }
            }

            Text{
               id:srvTip

                anchors{
                    left:parent.left
                    leftMargin: 30
                    verticalCenter: srvLineEdit.verticalCenter
                }
                text:qsTr("服务器")
                font.pixelSize: 30
            }

            CLineEdit {
                id: srvLineEdit

                anchors.top: logoInlogonImage.bottom
                anchors.left: parent.left
                anchors.leftMargin: srvLineEdit.text ==="" ? 165 : 0
                anchors.right: moreBtnRoot.left

                height: 85
                passwordLabelEnabled: false
                textLeftMargin: 90
                clip: true

                horizontalAlignment: srvLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入服务器")) // "请输入帐号"

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                text: "im"

                onTextChanged: {
                    passWordEdit.text = ""

                    if(loginPage.state !== "hidden") {
                        loginPage.state = "hidden"
                    }
                }
            }

            Text{
               id:srvUsr

                anchors{
                    left:parent.left
                    leftMargin: 30
                    verticalCenter: nameLineEdit.verticalCenter
                }

                text:qsTr("+86")
                font.pixelSize: 30
            }
            CLineEdit {
                id: nameLineEdit

                anchors.top: srvLineEdit.bottom
                anchors.left: parent.left
                anchors.leftMargin: nameLineEdit.text ==="" ? 165 : 0
                anchors.right: moreBtnRoot.left
                height: srvLineEdit.height

                passwordLabelEnabled: false
                textLeftMargin: 90
                clip: true

                horizontalAlignment: nameLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入手机号")) // "请输入帐号"

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                text: "11099999999"

                onTextChanged: {
                    passWordEdit.text = ""

                    if(loginPage.state !== "hidden") {
                        loginPage.state = "hidden"
                    }
                }
            }

            CLine {
                width: parent.width
                anchors.top: nameLineEdit.bottom
                z: parent.z+2
            }

            Rectangle{
                anchors.top: nameLineEdit.bottom
                anchors.left: parent.left
                height: passWordEdit.height
                width: parent.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        passWordEdit.focus = true;
                    }
                }
            }

            Text{
               id:srvPwd

                anchors{
                    left:parent.left
                    leftMargin: 30
                    verticalCenter: passWordEdit.verticalCenter
                }

                text:qsTr("密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: passWordEdit
                anchors.top: nameLineEdit.bottom
                anchors.left: parent.left
                anchors.leftMargin: passWordEdit.text ==="" ? 165 : 0
                anchors.right: moreBtnRoot.left
                height: nameLineEdit.height

                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 90
                clip: true
                horizontalAlignment: passWordEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入密码号")) // "密码"

                inputMethodHints:Qt.ImhHiddenText|Qt.ImhPreferLatin
                text: "999999"
            }

            CLine {
                width: parent.width
                anchors.top: passWordEdit.bottom
                z: parent.z+2
            }

            CButton {
                id: loginButton

                anchors.top: passWordEdit.bottom
                anchors.topMargin: 105
                anchors.horizontalCenter: parent.horizontalCenter
                height: 77
                width:655

                opacity : pressed ? 1: (nameLineEdit.text .trim()==="" || passWordEdit.text.trim() ==="" ? 0.5 : 1)
                text:os.i18n.ctr(qsTr("登 录")) // "登 录"
                textColor:  "#ffffff"

                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#32c2fe"
                    radius: 10
                }

                onClicked: {
                    console.log("login onClicked !!!")
                    if(nameLineEdit.text ==="" || passWordEdit.text ==="")
                        return;
                    if(loginManager.checkFirstWordIsSpace(nameLineEdit.text)) {
                        nameLineEdit.text = ""
                        nameLineEdit.focus = true
                        if(immanager.windowFocus)
                            gToast.requestToast("账号格式不正确","","");
                        return
                    }
                    if(nameLineEdit.text === "") {
                        nameLineEdit.focus = true
                        gToast.requestToast("帐号不能为空","","");
                    } else if(passWordEdit.text === "") {
                        passWordEdit.focus = true
                        gToast.requestToast("密码不能为空","","");
                    } else {
                        loadingDialog.show();
                        loginManager.login(srvLineEdit.text, nameLineEdit.text, passWordEdit.text);
                    }
                }

                Behavior on opacity {
                    PropertyAnimation { duration: 200 }
                }
            }

            CIndicatorDialog {
                id:loadingDialog
    //            indicatorDirection: Qt.Horizontal
                messageText: os.i18n.ctr(qsTr("正在登录中...")) // qsTr("正在登录中...")
            }

        }
    }
}
