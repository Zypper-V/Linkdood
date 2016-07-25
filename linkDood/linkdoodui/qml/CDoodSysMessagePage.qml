import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: sysMsgPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            sysMsgPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(sysMsgPage.statusBarHoldEnabled)
            sysMsgPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }else if(status === CPageStatus.Hide){
            console.log("2222222222222:hide")
            sysmsgManager.clearListView();
            sessionListManager.exitSysMsgPage();
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: sysMsgBackground
            anchors.fill: parent
            color: "#f2f2f2"
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
                    sysmsgManager.clearListView();
                    sessionListManager.exitSysMsgPage();
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("系统消息")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }
        Rectangle{
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color:"#F2F2F2"
            ListView {
                id: sysMsgListView
                clip: true
                model: sysmsgManager
                spacing:20

                anchors.fill: parent
                anchors.topMargin: 30

                delegate:Item {
                    id:sysMsgListDelegate

                    width: parent.width
                    height: 180

                    MouseArea {
                        anchors.fill: parent

                        onPressed: {
                            delegateBk.color = "#cdcdcd"
                        }
                        onReleased: {
                            delegateBk.color = "white"
                        }
                        onCanceled: {
                            delegateBk.color = "white"
                        }
                    }

                    Rectangle {
                        id:delegateBk

                        width: sysMsgListDelegate.width - 40
                        height: sysMsgListDelegate.height
                        radius: 10
                        color:"white"

                        anchors.centerIn: parent

                        Rectangle {
                            id : background

                            color:"transparent"
                            anchors.fill: parent
                            anchors.margins: 20

                            Text{
                                id:msgText
                                text:model.modelData.msgtypeText
                                font.pixelSize: 30
                                color:"#777777"

                                anchors.top: parent.top
                                anchors.left: parent.left
                            }
                            Text{
                                id:msgTime
                                text:model.modelData.time
                                font.pixelSize: 30
                                color:"#777777"

                                anchors.top: parent.top
                                anchors.right: parent.right
                            }
                            CLine{
                                id:line
                                anchors.top: msgText.bottom
                                anchors.topMargin: 8
                            }

                            Text{
                                id:msgIsReaded
                                text:model.modelData.respons
                                font.pixelSize: 28
                                color:"#777777"

                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                            }

                            CDoodHeaderImage {
                                id: headPortraitImage

                                width: 90
                                height: 90
                                radius: 6
                                name:""
                                iconSource: "qrc:/res/group_icon.png"/*"file://"+ model.modelData.thumbAvatar*/

                                anchors.left: parent.left
                                anchors.top:line.bottom
                                anchors.topMargin: 10
                            }
                            Text{
                                id:msgUserName
                                text:model.modelData.name
                                font.pixelSize: 30

                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 20
                                anchors.top: headPortraitImage.top
                                anchors.topMargin: 10
                            }
                            Text{
                                id:msgUserInfo
                                text:model.modelData.info
                                font.pixelSize: 26
                                color:"#777777"

                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 20
                                anchors.top: msgUserName.bottom
                                anchors.topMargin: 10
                            }

                            CButton {
                                id: btnAgree

                                height:50
                                width:70
                                opacity : pressed ? 1: 0.5
                                text:os.i18n.ctr(qsTr("同意"))
                                textColor:  "#ffffff"
                                visible: model.modelData.isShowButton

                                anchors.right: parent.right
                                anchors.top: msgUserName.top
                                anchors.topMargin: 10
                                backgroundComponent: Rectangle {
                                    anchors.fill: parent
                                    color:"#32c2fe"
                                    radius: 10
                                }
                                Behavior on opacity {
                                    PropertyAnimation { duration: 200 }
                                }
                                onClicked: {
                                    sysmsgManager.clickItem(model.modelData.msgid,true);
                                }
                            }
                            CButton {
                                id: btnIg

                                height:btnAgree.height
                                width:btnAgree.width
                                opacity : pressed ? 1: 0.5
                                text:os.i18n.ctr(qsTr("拒绝"))
                                textColor:  "#ffffff"
                                visible: model.modelData.isShowButton

                                anchors.right: btnAgree.left
                                anchors.rightMargin: 20
                                anchors.top: msgUserName.top
                                anchors.topMargin: 10
                                backgroundComponent: Rectangle {
                                    anchors.fill: parent
                                    color:"#32c2fe"
                                    radius: 10
                                }
                                Behavior on opacity {
                                    PropertyAnimation { duration: 200 }
                                }
                                onClicked: {
                                    sysmsgManager.clickItem(model.modelData.msgid,false);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

