import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: memberTipPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            memberTipPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(memberTipPage.statusBarHoldEnabled)
            memberTipPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: userdataBackground
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
                    //                    memberManager.clearMemberList();
                    pageStack.pop();
                }
            }
            Text{
                text:memberManager.memberSize===""?qsTr("选择要提醒的人(列表获取中...)"):qsTr("选择要提醒的人")
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
                id: orgListView
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom



                clip: true
                model: memberManager
                section.property: "modelData.sectionKey"
                section.criteria: ViewSection.FullString
                section.delegate: Rectangle {
                    width: memberTipPage.width
                    height: 35
                    color: "#F2F2F2"

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter
                        text: section
                        font.pixelSize: 22
                        color: "#333333"
                        onTextChanged: {
                            console.log("xxxxxx:"+text)
                        }
                    }
                }

                delegate:Item {
                    id:contactListDelegate

                    width: parent.width
                    height: 100
                    MouseArea {
                        id:mousea
                        anchors.fill: parent
                        property bool bPress
                        property bool bMove
                        onPressed: {
                            background.color = "#cdcdcd"
                        }
                        onReleased: {
                            background.color = "white"
                            chatManager.groupChatTipMember(model.modelData.groupid,model.modelData.id,model.modelData.name);
                            groupManager.addTipMember(model.modelData.groupid,model.modelData.id);
                            pageStack.pop();
                        }

                        onCanceled: {
                            background.color = "white"
                        }
                    }

                    Rectangle {
                        width: contactListDelegate.width
                        height: contactListDelegate.height
                        color:"white"
                        Rectangle {
                            id : background
                            anchors.fill: parent
                            color:"white"

                            CDoodHeaderImage {
                                id: headPortraitImage
                                anchors.left: parent.left
                                anchors.leftMargin: 25
                                anchors.topMargin: 16
                                anchors.verticalCenter: parent.verticalCenter
                                width: 90
                                height: 90
                                radius: 6
                                name:""
                                iconSource:setIcon("1",model.modelData.thumbAvatar)
                            }
                            Text {
                                id: nameText
                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 30
                                anchors.rightMargin: 20
                                anchors.top: parent.top
                                anchors.topMargin: 20
                                font.pixelSize: 24
                                height: 33
                                clip: true
                                color: "#333333"
                                verticalAlignment: Text.AlignVCenter
                                elide: Text.ElideRight
                                text: model.modelData.remark
                            }
                            CLine {
                                //                            width: parent.width
                                width: 3
                                anchors.left: parent.left
                                color:"#cdcdcd"
                                anchors.leftMargin: 25
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                z: parent.z+2
                            }
                        }
                    }
                }
            }
        }
    }
}
