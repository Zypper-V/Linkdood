import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupSetPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupSetPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupSetPage.statusBarHoldEnabled)
            groupSetPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: groupManager
        onRemoveGroupResult: {
            loadingDialog.hide();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
            //           pageStack.pop();
        }
        onGetGroupFileListResult:{
            loadingDialog.hide();
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
        onWordsOutOfLimited:{
            gToast.requestToast(tip,"","");
        }
    }
    contentAreaItem:Item {
        anchors.left :parent.left
        anchors.top:parent.top
        anchors.right: parent.right
        height: 3000


            Rectangle {
                id: userdataBackground
                anchors.fill: parent
                color: "#f2f2f2"
            }
            Rectangle{
                id: titleBackground
                z: 99

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
//                        memberManager.clearMemberList();
                        pageStack.pop();
                    }
                }
                Text{
                    text:qsTr("群设置")
                    color:"white"
                    font.pixelSize: 36
                    anchors.centerIn: parent
                }
            }

            Flickable{
                anchors.left:parent.left
                anchors.top:titleBackground.bottom
                width: parent.width
                height: groupSetPage.width
                contentWidth: width
                contentHeight: height + 30

            Rectangle{
                id:groupIcon
                anchors.left:parent.left
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.leftMargin: 40
                width: 90
                height: 90
                border.width: 1
                radius: 20
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        if(groupManager.isGroupLeader){
//                        console.log(groupManager.thumbAvatar);
//                        groupManager.getGroupFileList(groupManager.id);
                        var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodGroupViewImagePage.qml"),"CDoodGroupViewImagePage");
                        pageStack.push(component);
                        }
                    }
                }

                CDoodHeaderImage{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 90
                    height: 90
                    radius: 6

                    iconSource:setIcon("2",groupManager.thumbAvatar)

                }
//                Image{

//                    anchors.fill: parent

//                    //                anchors.centerIn: parent
//                    //                width: parent.width-1
//                    //                height: parent.height-1
//                    source: groupManager.thumbAvatar===""?"qrc:/res/group_icon.png":"file:///data/data/com.vrv.linkDood/public/head/"+groupManager.thumbAvatar
//                }
            }

            Text{
                id:groupName
                font.pixelSize: 32
                anchors.left:groupIcon.right
                anchors.leftMargin: 30
                anchors.top:parent.top
                anchors.topMargin: 40
                color:"black"
                width:500
                elide: Text.ElideRight
                text:groupManager.name
            }
            Text{
                id:groupId
                font.pixelSize: 22
                anchors.left:groupIcon.right
                anchors.leftMargin: 30
                anchors.top:groupName.bottom
                anchors.topMargin: 15
                color:"black"
                text:groupManager.id
            }
            Rectangle {
                id:bascicBackground

                color:"white"
                border.width: 1
                border.color: "#cdcdcd"
                radius: 20
                height: 180

                anchors.top: parent.top
                anchors.topMargin: 134
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                UserProfileButton{
                    id:allMember
                    height: 90
                    leftText: qsTr("群成员列表")
                    editable:true
                    anchors.top:parent.top
                    anchors.topMargin: 7
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    onClicked: {
//                        memberManager.clearMemberList();
//                        groupManager.getMemberList(groupManager.id);
                        pageStack.push(Qt.resolvedUrl("CDoodMemberListPage.qml"));
                        //                    loadingDialog.show();
                    }
                }
                UserProfileButton{
                    id:inviteMember
                    height: 60
                    leftText: qsTr("邀请群成员")
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    editable:true
                    showLine:false
                    anchors.top: allMember.bottom
                    onClicked: {
                        groupManager.setIsCreateGroup(false);
                        pageStack.push(Qt.resolvedUrl("CDoodGroupAddMainPage.qml"));
                    }
                }
            }
            Rectangle {
                id:groupinfoBackground

                color:"white"
                border.width: 1
                border.color: "#cdcdcd"
                radius: 30
                height: 202

                anchors.top: bascicBackground.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                UserProfileButton{
                    id:group_name
                    height: 90

                    leftText: qsTr("群名称")
                    editable:true
                    rigthText:groupManager.name
                    anchors.top:parent.top
                    anchors.topMargin: 7
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    //                width:400
                    onClicked: {
                        if(groupManager.isGroupLeader||memberManager.my_Type==="2"){
                            inputDialog.titleText= qsTr("群名称");
                            inputDialog.setText(rigthText);
                            inputDialog.type = 2;
                            inputDialog.show();
                        }
                        else{
                            gToast.requestToast(rigthText,"","");
                        }
                    }
                }
                UserProfileButton{
                    id:groupbrief
                    height: 90
                    leftText: qsTr("群简介")
                    rigthText: groupManager.brief===""?qsTr("无"):groupManager.brief
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    editable:true
                                    showLine:false
                    anchors.top: group_name.bottom
                    onClicked: {
                        if(groupManager.isGroupLeader||memberManager.my_Type==="2"){
                            inputDialog.titleText= qsTr("群简介");
                            if(rigthText==="无"){
                               inputDialog.setText("");
                            }
                            else{
                            inputDialog.setText(rigthText);
                            }
                            inputDialog.type = 3;
                            inputDialog.show();
                        }
                        else{
                            gToast.requestToast(rigthText,"","");
                        }
                    }
                }
//                UserProfileButton{
//                    id:groupbull
//                    height: 90
//                    leftText: qsTr("群公告")
//                    rigthText:groupManager.bulletin===""?qsTr("无"):groupManager.bulletin
//                    anchors.left:parent.left
//                    anchors.right: parent.right
//                    anchors.rightMargin: 7
//                    anchors.leftMargin: 7
//                    editable:true
//                    //                showLine:false
//                    anchors.top: groupbrief.bottom
//                    onClicked: {
//                        if(groupManager.isGroupLeader){
//                            inputDialog.titleText= qsTr("群公告");
//                            inputDialog.setText(rigthText);
//                            inputDialog.type = 4;
//                            inputDialog.show();
//                        }
//                        else{
//                            gToast.requestToast(rigthText,"","");
//                        }
//                    }
//                }
//                UserProfileButton{
//                    id:groupFileList
//                    height: 90
//                    leftText: qsTr("查看群文件")
//                    anchors.left:parent.left
//                    anchors.right: parent.right
//                    anchors.rightMargin: 7
//                    anchors.leftMargin: 7
//                    editable:true
//                    showLine:false
//                    anchors.top: groupbull.bottom
//                    onClicked: {
////                        groupManager.getGroupFileList(groupManager.id);
//                    }
//                }
            }
            Rectangle {
                id:groupsetBackground

                color:"white"
                border.width: 1
                border.color: "#cdcdcd"
                radius: 30
                height: 195

                anchors.top: groupinfoBackground.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                UserProfileButton{
                    id:group_verifyType
                    height: 90

                    leftText: qsTr("身份验证")
                    editable:true
                    rigthText:groupManager.verify_type
                    anchors.top:parent.top
                    anchors.topMargin: 7
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    onClicked: {
                        if(groupManager.isGroupLeader||memberManager.my_Type==="2"){
                        verifyListDialog.deselect();
                        verifyListDialog.select(verifyListDialog.initSelect(),true);
                        verifyListDialog.show();
                        }
                        else{
                           gToast.requestToast(rigthText,"","");
                        }
                    }
                }
                UserProfileButton{
                    id:group_isAllow
                    height: 90
                    leftText: qsTr("允许群成员邀请好友加入")
                    rigthText: groupManager.is_allow
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 7
                    anchors.leftMargin: 7
                    editable:true
                    showLine:false
                    anchors.top: group_verifyType.bottom
                    onClicked: {
                        if(groupManager.isGroupLeader||memberManager.my_Type==="2"){
                        is_AllowListDialog.deselect();
                        is_AllowListDialog.select(is_AllowListDialog.initSelect(),true);
                        is_AllowListDialog.show();
                        }
                        else{
                            gToast.requestToast(rigthText,"","");
                        }
                    }
                }
            }
            Rectangle{
                id:deletegroup

                border.width: 1
                border.color: "#777777"
                radius: 10
                color:"white"
                height: 100

                Text{
                    text:groupManager.isGroupLeader===true?qsTr("解散该群"):qsTr("退出该群")
                    font.pixelSize: 34
                    color:"red"
                    anchors.centerIn: parent
                }
                anchors.top:groupsetBackground.bottom
                anchors.topMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin:20
                MouseArea{
                    anchors.fill: parent
                    onPressed: deletegroup.color = "#cdcdcd"
                    onReleased: deletegroup.color = "white"
                    onClicked: {
                        //                    groupManager.removeGroup(groupManager.id);
                        if(groupManager.isGroupLeader){
                            alertDialog.operate="是否解散该群";
                        }
                        else{
                            alertDialog.operate="是否退出该群";
                        }

                        alertDialog.show();
                    }
                }
            }
            onFlickEnded: {
//                groupFileList.color = "white"
//                groupbull.color = "white"
                groupbrief.color = "white"
                group_name.color = "white"
                inviteMember.color = "white"
                allMember.color = "white"
            }
            }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在操作中..."))
    }
    CInputDialog{
        id:inputDialog
        maximumLength:inputDialog.type===3?40:25
        property int  type
        messageTextColor:"#777777"
        onAccepted: {
            groupManager.setGroupInfo(type,inputDialog.text());
        }
    }
    CDialog {
        property string operate: ""
        id: alertDialog

        titleText: qsTr("提示")
        messageText: alertDialog.operate
        onAccepted: {
            groupManager.removeGroup("",groupManager.id);
            loadingDialog.show();
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDoodListDialog{
        id: verifyListDialog

        titleText: qsTr("身份验证")
        onNotifySelectedItems:{
            console.log("xxxxxxxxx:"+model[curIndex]);
            groupManager.setGroupSet(1,model[curIndex]);
        }
        Component.onCompleted: {
            model = [qsTr("不允许加群"),qsTr("需要验证"),qsTr("允许任何人加群")]
        }
        function initSelect(){
            if(groupManager.verify_type === qsTr("不允许加群")){
                return 0;
            }
            if(groupManager.verify_type === qsTr("需要验证")){
                return 1;
            }
            return 2;
        }
    }
    CDoodListDialog{
        id: is_AllowListDialog

        titleText: qsTr("允许群成员邀请好友加入")
        onNotifySelectedItems:{
            console.log("xxxxxxxxx:"+model[curIndex]);
            groupManager.setGroupSet(2,model[curIndex]);
        }
        Component.onCompleted: {
            model = [qsTr("允许邀请"),qsTr("不允许邀请")]
        }
        function initSelect(){
            if(groupManager.is_allow === qsTr("允许邀请")){
                return 0;
            }
            if(groupManager.is_allow === qsTr("不允许邀请")){
                return 1;
            }
        }
    }

}
