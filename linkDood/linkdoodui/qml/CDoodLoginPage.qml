import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: loginPage
    anchors.fill: parent

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            loginPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(loginPage.statusBarHoldEnabled)
            loginPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("transblack")
        }
    }

//    Connections {
//        target: loginManager

//        onInputRootTabView: {
//            console.log("onInputRootTabView !!!!")
//            pageStack.replace(Qt.resolvedUrl("CPortalRootTabView.qml"), "", true);
//        }

//        onLoginSuccess: {
//            console.log("onLoginSuccess !!!!")
//            loadingDialog.hide();
//            pageStack.replace(Qt.resolvedUrl("CPortalRootTabView.qml"), "", true);
//        }

//        onLoginFailed: {
//            console.log("onLoginFailed !!!!")
//            loadingDialog.hide();
//            gToast.requestToast("登陆失败","","");
//        }
//    }

    contentAreaItem: Item {
        anchors.fill :parent
        Rectangle {
            id: loginBackground
            anchors.fill: parent
            color: "#edf0f0"
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



            Item {
                id: logoInlogonImage

                anchors.top: parent.top
                anchors.topMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter

                width: parent.width
                height: 128

                Image {
                    id: logoImage
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
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
                anchors.top: nameLineEdit.top
                anchors.bottom: passWordEdit.bottom
                width: parent.width
                color: "#ffffff"
            }

            CLine {
                width: parent.width
                anchors.bottom: nameLineEdit.top
                z: parent.z+2
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

            Rectangle{
                anchors.top: logoInlogonImage.bottom
                anchors.topMargin: 28
                anchors.left: parent.left
                height: 120
                z: moreBtnRoot.z - 5
                width: parent.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        nameLineEdit.focus = true;
                    }
                }
            }

            CLineEdit {
                id: nameLineEdit
                anchors.top: logoInlogonImage.bottom
                anchors.topMargin: 28
                anchors.left: parent.left
                anchors.leftMargin: nameLineEdit.text ==="" ? 165 : 0
                anchors.right: moreBtnRoot.left
                height: 120

                passwordLabelEnabled: false
                textLeftMargin: 90
                clip: true

                horizontalAlignment: nameLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入帐号")) // "请输入帐号"

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
//                text: cimloginmanager.getCurrentUserId()

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
                height: 120
                width: parent.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        passWordEdit.focus = true;
                    }
                }
            }

            CLineEdit {
                id: passWordEdit
                anchors.top: nameLineEdit.bottom
                anchors.left: parent.left
                anchors.leftMargin: passWordEdit.text ==="" ? 225 : 0
                anchors.right: moreBtnRoot.left
                height: nameLineEdit.height

                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 90
                clip: true
                horizontalAlignment: passWordEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("密码")) // "密码"

                inputMethodHints:Qt.ImhHiddenText|Qt.ImhPreferLatin
//                text: cimloginmanager.getCurrentUserPassword()
            }

            CLine {
                width: parent.width
                anchors.top: passWordEdit.bottom
                z: parent.z+2
            }

            CButton {
                id: loginButton
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.top: passWordEdit.bottom
                anchors.topMargin: 80
                height: 100

                opacity : pressed ? 1: (nameLineEdit.text .trim()==="" || passWordEdit.text.trim() ==="" ? 0.5 : 1)
                text:os.i18n.ctr(qsTr("登 录")) // "登 录"
                textColor:  "#ffffff"

                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#00B1EE"
                    radius: 10
                }

                onClicked: {
                    console.log("login onClicked !!!")
//                    if(nameLineEdit.text ==="" || passWordEdit.text ==="")
//                        return;
//                    if(loginManager.checkFirstWordIsSpace(nameLineEdit.text)) {
//                        nameLineEdit.text = ""
//                        nameLineEdit.focus = true
//                        if(immanager.windowFocus)
//                            gToast.requestToast("账号格式不正确","","");
//                        return
//                    }
//                    if(nameLineEdit.text === "") {
//                        nameLineEdit.focus = true
//                        gToast.requestToast("帐号不能为空","","");
//                    } else if(passWordEdit.text === "") {
//                        passWordEdit.focus = true
//                        gToast.requestToast("密码不能为空","","");
//                    } else {
//                        loadingDialog.show();
//                        loginManager.login(nameLineEdit.text, passWordEdit.text);
//                    }
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
