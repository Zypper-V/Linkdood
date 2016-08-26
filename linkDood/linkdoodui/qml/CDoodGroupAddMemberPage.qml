import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item {
    id: groupAddMemberPage

    property bool isTransMsg: false

    anchors.fill: parent
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left

        width:parent.width
        height: parent.height

        color: "white"
        z:parent.z-1
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
                    if(groupManager.isCreateGroup){
                        var size=groupManager.getSize("1","0",groupManager.memberCount);
                        if(size==="1000"){
                            gToast.requestToast("群成员数不能超过1000","","");
                            return;
                        }
                    }
                    else{
                        var size=groupManager.getSize("1",memberManager.memberSize,groupManager.memberCount);
                        if(size==="1000"){
                            gToast.requestToast("群成员数不能超过1000","","");
                            return;
                        }
                    }

                    if(groupAddOrgPage.isTransMsg){
                        groupManager.selectmember(model.modelData.id);
                        enterpriseManager.changeMember(groupManager.returnmember());
                        enterpriseManager.selectMember(model.modelData.id);
                        contactManager.selectMember(model.modelData.id);

                    }else{
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

                            if(groupAddMemberPage.isTransMsg){
                                if(model.modelData.isChoose===""){
                                    return "qrc:/res/group_select_cbox_normal.png";
                                }
                                else{
                                    return "qrc:/res/group_select_cbox_press.png";
                                }
                            }

                            if(groupManager.isCreateGroup){
                                if(model.modelData.isChoose===""){
                                    return "qrc:/res/group_select_cbox_normal.png";
                                }
                                else{
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
                        //headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                        iconSource: setIcon("1",model.modelData.thumbAvatar)
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
    //    CIndicatorDialog {
    //        id:loadingDialog
    //        //            indicatorDirection: Qt.Horizontal
    //        messageText: os.i18n.ctr(qsTr("正在操作中..."))
    //    }
    CInputDialog{
        id:inputDialog
        messageTextColor:"#777777"
        onAccepted: {
            groupManager.createGroup(inputDialog.text());
            loadingDialog.show();
        }
    }
}

