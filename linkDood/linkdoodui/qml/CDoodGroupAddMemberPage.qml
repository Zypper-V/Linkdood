import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item {
    id: groupAddMemberPage
    anchors.fill: parent
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left

        width:parent.width
        height: parent.height

        color: "white"
        z:parent.z-1
    }

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
    Connections {
        target: groupManager
        onCreateGroupResult: {
            console.log("!!!!")
            loadingDialog.hide();
            contactManager.clearMember();
            enterpriseManager.clearMember();
            groupManager.clearMemberCount();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
        onInviteMemberResult: {
            console.log("!!!!")
            loadingDialog.hide();
            contactManager.clearMember();
            enterpriseManager.clearMember();
            groupManager.clearMemberCount();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }

    }
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
                    if(groupManager.isCreateGroup){
                        groupManager.selectmember(model.modelData.id);
                        enterpriseManager.changeMember(groupManager.returnmember());
                        contactManager.selectMember(model.modelData.id);
                        enterpriseManager.selectMember(model.modelData.id);
                    }
                    else{
                        if(!memberManager.isMember(model.modelData.id)){
                            groupManager.selectmember(model.modelData.id);
                            enterpriseManager.changeMember(groupManager.returnmember());
                            contactManager.selectMember(model.modelData.id);
                            enterpriseManager.selectMember(model.modelData.id);
                        }
                    }
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
                        source:select()
                        function select(){
                            if(groupManager.isCreateGroup){
                                if(model.modelData.isChoose===""){
                                    console.log("111");
                                    return "qrc:/res/group_select_cbox_normal.png";
                                }
                                else{
                                    console.log("222");
                                    return "qrc:/res/group_select_cbox_press.png";
                                }
                            }
                            else{
                                if(memberManager.isMember(model.modelData.id)){
                                    return "qrc:/res/group_select_cbox_have.png";
                                }
                                if(model.modelData.isChoose===""){
                                    return "qrc:/res/group_select_cbox_normal.png";
                                }
                                else{
                                    return "qrc:/res/group_select_cbox_press.png";
                                }
                            }

                        }
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
    //        }
    //    }
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

