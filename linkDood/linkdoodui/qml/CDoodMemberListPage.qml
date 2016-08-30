import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: memberListPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            memberListPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(memberListPage.statusBarHoldEnabled)
            memberListPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: memberManager
        onWordsOutOfLimited:{
            gToast.requestToast(tip,"","");
        }
        onGetMemberInfoResult:{
            userdataManager.setName(name);
        }
    }
    Connections {
        target: groupManager
        onTransferGroupResult:{
            gToast.requestToast(result,"","");
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
                text:memberManager.memberSize===""?qsTr("群成员列表(获取中...)"):qsTr("群成员列表("+memberManager.memberSize+")")
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
                    width: memberListPage.width
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
                    Timer {
                        id:pressTimer

                        interval: 500
                        repeat: false
                        onTriggered:{
                            if(mousea.bPress && !mousea.bMove){
                                menu.id = model.modelData.id;
                                menu.member_type= model.modelData.member_type;
                                menu.name  = model.modelData.remark;
                                menu.groupid=model.modelData.groupid;
                                if(memberManager.isTip==="1"){
                                    menu.show();
                                }
                                if(memberManager.isMyself(model.modelData.id)){
                                    menu1.id=model.modelData.id;
                                    menu1.groupid=model.modelData.groupid;
                                    menu1.name=model.modelData.remark;
                                    menu1.show();
                                }
                            }
                            pressTimer.stop();
                        }
                    }

                    MouseArea {
                        id:mousea
                        anchors.fill: parent
                        property bool bPress
                        property bool bMove
                        onPressed: {
                            background.color = "#cdcdcd"
                            bMove  = false;
                            bPress = true;
                            pressTimer.start();
                            memberManager.judgeTip(model.modelData.member_type);

                        }
                        onPositionChanged: {
                            bMove = true;
                        }

                        onReleased: {
                            background.color = "white"
                            bPress = false;
                            bMove  = false;
                            if(pressTimer.running){
                                pressTimer.stop();
                                userdataManager.setName(model.modelData.name);
                                memberManager.getMemberInfo(model.modelData.groupid,model.modelData.id);
                                userdataManager.clearData();
                                userdataManager.setRemark(model.modelData.name);
                                userdataManager.setGender(model.modelData.gender);
                                userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                                userdataManager.setId(model.modelData.id);
                                userdataManager.setIsFriend("1");
                                pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));

                            }
                            //pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));
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
    CDoodPopWndLayer{
        id:menu
        property string member_type
        property string id: ""
        property string name: ""
        property string groupid: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: memberManager.my_Type==="3"?510:310
            Text{
                id:title

                text:qsTr("提示")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line

                anchors.top:title.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btnStar
                visible: memberManager.my_Type==="3" ? true : false
                width:parent.width
                height: 100
                leftText: menu.member_type ==="1"?qsTr("提升为管理员") :qsTr("取消管理员") ;
                radius: 4

                anchors.top: line.bottom
                anchors.topMargin: 10

                onClicked: {
                    menu.hide();

                    console.log("33333333333333333333333333")
                    alertDialog_Mem.id=menu.id;
                    alertDialog_Mem.groupid=menu.groupid;
                    alertDialog_Mem.member_type=menu.member_type;
                    if(menu.member_type == "1"){
                        alertDialog_Mem.operate="是否提升 "+menu.name+" 为管理员"
                        //                        memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","2");
                    }else{
                        alertDialog_Mem.operate="是否取消 "+menu.name+" 管理员权限"
                        //                        memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","1");
                    }
                    alertDialog_Mem.show();
                    //                    indicatorDialog.show();
                }
            }
            UserProfileButton{
                id:btntran

                width:parent.width
                height: 100
                leftText: qsTr("修改群名片")
                radius: 4

                anchors.top: memberManager.my_Type==="3" ?btnStar.bottom:line.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();

                    inputDialog.id=menu.id;
                    inputDialog.groupid=menu.groupid;
                    inputDialog.setText(menu.name);
                    inputDialog.show();
                }
            }
            UserProfileButton{
                id:btnDel

                width:parent.width
                height: 100
                leftText: qsTr("移除群成员")
                radius: 4
                showLine:memberManager.my_Type==="3" ? true : false
                anchors.top: btntran.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    alertDialog_deleMem.operate="是否移除群成员 "+menu.name;
                    alertDialog_deleMem.id=menu.id;
                    alertDialog_deleMem.groupid=menu.groupid;
                    alertDialog_deleMem.show();
                }
            }
            UserProfileButton{
                id:btnRemark
                visible: memberManager.my_Type==="3" ? true : false
                width:parent.width
                height:100
                leftText: qsTr("转让该群") ;
                radius: 4
                showLine:false

                anchors.top: btnDel.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    alertDialog_trans.operate="是否将本群转让给 "+menu.name;
                    alertDialog_trans.id=menu.id;
                    alertDialog_trans.groupid=menu.groupid;
                    alertDialog_trans.show();
                }
            }
        }

        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu.hide();
        }
    }
    CDoodPopWndLayer{
        id:menu1
        property string id: ""
        property string groupid: ""
        property string name: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 190
            Text{
                id:title1

                text:qsTr("提示")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line1

                anchors.top:title1.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btntran1

                width:parent.width
                height: 100
                leftText: qsTr("修改群名片")
                radius: 4

                anchors.top: line1.bottom
                anchors.topMargin: 10
                showLine:false
                onClicked: {
                    menu1.hide();

                    inputDialog.id=menu1.id;
                    inputDialog.groupid=menu1.groupid;
                    inputDialog.setText(menu1.name);
                    inputDialog.show();
                }
            }
        }
        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu1.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu1.hide();
        }
    }
    CInputDialog{
        id:inputDialog
        property string id: ""
        property string groupid: ""
        titleText: qsTr("修改群名片")
        messageTextColor:"#777777"
        onAccepted: {
            memberManager.setMemberInfo(inputDialog.groupid,inputDialog.id,"修改备注",inputDialog.text());
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        id: alertDialog_deleMem

        titleText: qsTr("提示")
        messageText: alertDialog_deleMem.operate
        onAccepted: {
            memberManager.removeMember(alertDialog_deleMem.groupid,alertDialog_deleMem.id);

        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        id: alertDialog_trans

        titleText: qsTr("提示")
        messageText: alertDialog_trans.operate
        onAccepted: {

            groupManager.transferGroup(menu.groupid,menu.id);
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        property string member_type: ""
        id: alertDialog_Mem

        titleText: qsTr("提示")
        messageText: alertDialog_Mem.operate
        onAccepted: {
            if(alertDialog_Mem.member_type == "1"){
                memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","2");
            }else{
                memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","1");
            }

        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
}
