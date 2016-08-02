import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: friendVerifyId

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            friendVerifyId.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(friendVerifyId.statusBarHoldEnabled)
            friendVerifyId.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: friendVerBackground
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
                id: titleBackground

                color:"#003953"
                width:parent.width
                height:86
                anchors{
                    top:parent.top
                    left:parent.left
                }
                IconButton{
                    id:btnBack
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        pageStack.pop();
                    }
                }
                Text{
                    text:qsTr("好友验证")
                    color:"white"
                    font.pixelSize: 36
                    anchors.centerIn: parent
                }

                Rectangle{
                    id:btnSend

                    height:86
                    width: 100
                    color:"#003953"

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10

                    Text{
                        text:qsTr("发送")
                        color:"white"
                        font.pixelSize: 36
                        anchors.centerIn: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            addContactManager.addContact(friendVericationManager.id,inputRemark.text,inputTextArea.text);
                            var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodRootTabView.qml"),"CDoodRootTabView");
                            pageStack.push(component);
                        }
                    }
                }
            }
            Rectangle{
                id:inforBg

                width:parent.width -80
                height:180
                color:"transparent"
                anchors.top: titleBackground.bottom
                anchors.horizontalCenter: parent.horizontalCenter

                CDoodHeaderImage {
                    id:headImage

                    width:160
                    height: 160
                    radius:10
                    name:""
                    iconSource: setIcon("1",friendVericationManager.thumbAvatar)
//                        friendVericationManager.thumbAvatar !=="" ?friendVericationManager.thumbAvatar :"qrc:/res/headerDefault.png"

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left:parent.left
                }
                Text{
                    id:userName

                    text:friendVericationManager.name
                    font.pixelSize: 28
                    color:"#333333"

                    anchors.left: headImage.right
                    anchors.leftMargin: 10
                    anchors.top: headImage.top
                    anchors.topMargin: 40
                }

                Text{
                    id:userLinkDood

                    text:"发起群聊"
                    font.pixelSize: 28
                    color:"#333333"
                    visible: false

                    anchors.left: headImage.right
                    anchors.leftMargin: 10
                    anchors.top: userName.bottom
                    anchors.topMargin: 30
                }
            }


            Text{
                id:tipInput

                text:qsTr("验证信息:")
                font.pixelSize: 28
                color:"#333333"

                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.top:inforBg.bottom
                anchors.topMargin: 20
            }
            Rectangle{
                id:inputUserInfor

                anchors.top: tipInput.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                width:parent.width-80
                height: 200
                radius: 10
                CTextArea {
                    id: inputTextArea

                    anchors.fill: parent
                    text:qsTr("我是")+friendVericationManager.myName
                    textColor: "#333333"
                    font.pixelSize: 28
                    maximumLength: 500
                    textMargin: 12
                    wrapMode: TextEdit.Wrap
                    focus:true
                }
            }
            Text{
                id:tipRemark

                text:qsTr("备注:")
                font.pixelSize: 28
                color:"#333333"

                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.top:inputUserInfor.bottom
                anchors.topMargin: 10
            }
            Rectangle{
                id: background
                width: parent.width-80
                height: 80
                radius: 10

                anchors.top: tipRemark.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                CLineEdit {
                    id:inputRemark

                    anchors.fill: parent
                }
            }
        }
    }
}
