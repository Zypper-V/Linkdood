import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: memberTipPage
    property string  groupid


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
                    memberManager.clearMember();
                    pageStack.pop();
                }
            }
            Text{
                text:memberManager.memberSize===""?qsTr("选择提醒的人(获取中...)"):qsTr("选择提醒的人")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
            CButton{
                id:surbutton
                anchors.right:parent.right
                anchors.rightMargin: 5
                width: 150
                anchors.verticalCenter: parent.verticalCenter
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#003953"
                    radius: 10
                }
                onClicked: {
                    chatManager.groupChatTipMember(memberManager.getTipName());
                    groupManager.addTipMember(memberTipPage.groupid,memberManager.getTipMember());
                    memberManager.clearMember();
                    pageStack.pop();
                }
                Text{
                    text:qsTr("确定")
                    color:"white"
                    font.pixelSize: 32
                    //                    anchors.centerIn: parent
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                }
            }
        }
        Rectangle{
            id:allmember
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 100
            MouseArea {
                id:mousea1
                anchors.fill: parent
                onPressed: {
                    allmember.color = "#cdcdcd"
                }
                onReleased: {
                    allmember.color = "white"
                    chatManager.groupChatTipMember("@全体成员"+"\x1D");
                    groupManager.addTipAllMember(memberTipPage.groupid);
                    memberManager.clearMember();
                    pageStack.pop();
                }

                onCanceled: {
                    allmember.color = "white"
                }
            }
            CDoodHeaderImage {
                id: headPortraitImage1
                anchors.left: parent.left
                anchors.leftMargin: 25
                anchors.topMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                width: 90
                height: 90
                radius: 6
                name:""
                iconSource:setIcon("1","")
            }
            Text {
                id: nameText1
                anchors.left: headPortraitImage1.right
                anchors.leftMargin: 30
                anchors.rightMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 25
                font.pixelSize: 28
                height: 33
                clip: true
                color: "#333333"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "@全体成员"
            }

        }

        Rectangle{
            anchors.top: allmember.bottom
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
                    width:memberTipPage.width
                    visible: !(section==="群主"||section==="管理员")
                    height:(section==="群主"||section==="管理员")?0:35
                    color: "#F2F2F2"

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter
                        text: (section==="群主"||section==="管理员")?"":section
                        font.pixelSize: 22
                        color: "#333333"
                        onTextChanged: {
                            console.log("xxxxxx:"+text)
                        }
                    }
                }

                delegate:Item {
                    id:contactListDelegate
                    visible: !(model.modelData.sectionKey==="群主"||model.modelData.sectionKey==="管理员")
                    width: parent.width
                    height: (model.modelData.sectionKey==="群主"||model.modelData.sectionKey==="管理员")===true?0:100
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
                            if(memberManager.isMyself(model.modelData.id)){
                                gToast.requestToast("不能@自己","","");
                                return;
                            }
                            memberManager.selectMember(model.modelData.id);
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
                            Image{
                                id:chooseImage
                                anchors.left: parent.left
                                anchors.leftMargin: 25
                                anchors.topMargin: 16
                                anchors.verticalCenter: parent.verticalCenter
                                source:model.modelData.isChoose===""?"qrc:/res/group_select_cbox_normal.png":"qrc:/res/group_select_cbox_press.png"
                            }

                            CDoodHeaderImage {
                                id: headPortraitImage
                                anchors.left: parent.left
                                anchors.leftMargin: 105
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
