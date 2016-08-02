import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupAddMemberPage

    property string localId

    states: [
        State {
            name: "forwordMsg"
        },
        State {
            name: "groupMng"
        }
    ]
    state: "groupMng"
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupAddMemberPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupAddMemberPage.statusBarHoldEnabled)
            groupAddMemberPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: groupManager
        onCreateGroupResult: {
            console.log("!!!!")
            loadingDialog.hide();
            contactManager.clearMember();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
        onInviteMemberResult: {
            console.log("!!!!")
            loadingDialog.hide();
            contactManager.clearMember();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
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
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("选择好友")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
            CButton{
                id:surbutton
                anchors.right:parent.right
                anchors.rightMargin: 30
                width: 80
                anchors.verticalCenter: parent.verticalCenter
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#003953"
                    radius: 10
                }
                onClicked: {
                    if(groupAddMemberPage.state == "forwordMsg"){
                        //TODO
                        groupManager.transMessage(localId);
                        pageStack.pop();
                    }
                    else if(groupManager.isCreateGroup){
                        //                        inputDialog.titleText= qsTr("输入群名称");
                        //                        inputDialog.show();
                        groupManager.createGroup("");
                        loadingDialog.show();
                    }
                    else{
                        loadingDialog.show();
                        groupManager.inviteMember();
                    }
                }
                Text{
                    text:qsTr("确定")
                    color:"white"
                    font.pixelSize: 32
                    anchors.centerIn: parent
                }

            }
        }
        Rectangle{
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color:"#F2F2F2"

            ListView {
                id: contactListView
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom



                clip: true
                model: contactManager
                section.property: "modelData.sectionKey"
                section.criteria: ViewSection.FullString
                section.delegate: Rectangle {
                    width: groupAddMemberPage.width
                    height: section==="app"?0:38
                    color: "#F2F2F2"

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter
                        text:(section !== "app" ? section:"")
                        font.pixelSize: 26
                        color: "#333333"
                        onTextChanged: {
                            console.log("xxxxxx:"+text)
                        }
                    }
                }

                delegate:Item {
                    id:contactListDelegate

                    width: parent.width
                    height:model.modelData.sectionKey==="app"?0:100
                    visible: model.modelData.sectionKey==="app"?false:true

                    MouseArea {
                        anchors.fill: parent

                        onPressed: {
                            background.color = "#cdcdcd"
                        }

                        onReleased: {
                            background.color = "white"
                            //if(groupAddMemberPage.state != "forwordMsg")
                            groupManager.selectmember(model.modelData.id);
                            contactManager.selectMember(model.modelData.id);
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
                                source: model.modelData.isChoose===""? "qrc:/res/group_select_cbox_normal.png":"qrc:/res/group_select_cbox_press.png"
                            }

                            CDoodHeaderImage {
                                id: headPortraitImage
                                anchors.left: chooseImage.left
                                anchors.leftMargin: 80
                                anchors.topMargin: 16
                                anchors.verticalCenter: parent.verticalCenter
                                width: 90
                                height: 90
                                radius: 6
                                name:""
                                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                                iconSource: "qrc:/res/group_icon.png"/*"file://"+ model.modelData.thumbAvatar*/
                            }
                            Text {
                                id: nameText
                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 30
                                anchors.rightMargin: 20
                                anchors.top: parent.top
                                anchors.topMargin: 20
                                font.pixelSize: 24
                                height: 26
                                clip: true
                                color: "#333333"
                                verticalAlignment: Text.AlignVCenter
                                elide: Text.ElideRight
                                text: model.modelData.name
                            }
                            CLine {
                                //                            width: parent.width
                                width: 1
                                anchors.left: parent.left
                                //                                color:"#cdcdcd"
                                //                        anchors.leftMargin: 150
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                z: parent.z
                            }
                        }
                    }
                }
            }
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        //            indicatorDirection: Qt.Horizontal
        messageText: os.i18n.ctr(qsTr("正在操作中..."))
    }
    CInputDialog{
        id:inputDialog
        messageTextColor:"#777777"
        onAccepted: {
            groupManager.createGroup(inputDialog.text());
            loadingDialog.show();
        }
    }
}

