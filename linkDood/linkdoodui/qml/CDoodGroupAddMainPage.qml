import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupAddMainPage

    property bool isTransMessage: false
    property string localId

    anchors.fill: parent
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupAddMainPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupAddMainPage.statusBarHoldEnabled)
            groupAddMainPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: groupManager
        onNoMemberInvited:{
            loadingDialog.hide();
            gToast.requestToast(tip,"","");
        }
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
            pageStack.pop();
            //            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
        onNewGroupToChat:{
            console.log("!1111!")
            console.log("!!!!")
            loadingDialog.hide();
            contactManager.clearMember();
            enterpriseManager.clearMember();
            groupManager.clearMemberCount();
            memberManager.clearMemberList();
            if(id==="0"){
                gToast.requestToast("获取新群信息时出错","","");
                pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
            }
            else{
                chatManager.switchToChatPage(id,name,"2","0",0,"");
            }
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
                    contactManager.clearMember();
                    enterpriseManager.clearMember();
                    groupManager.clearMemberCount();
                    pageStack.pop();
                }
            }
            Text{
                text:isTransMessage ? qsTr("选择转发人员"): qsTr("选择成员")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
            CButton{
                id:surbutton
                anchors.right:parent.right
                anchors.rightMargin: 5
                width: 200
                anchors.verticalCenter: parent.verticalCenter
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#003953"
                    radius: 10
                }
                onClicked: {
                    if(groupAddMainPage.isTransMessage){
                        //TODO
                        groupManager.transMessage(groupAddMainPage.localId);
                        pageStack.pop();
                    }
                    else if(groupManager.isCreateGroup){
                        //                        inputDialog.titleText= qsTr("输入群名称");
                        //                        inputDialog.show();
                        loadingDialog.show();
                        groupManager.createGroup("");

                    }
                    else{
                        loadingDialog.show();
                        groupManager.inviteMember();
                    }
                }
                Text{
                    text:qsTr("确定")+size()
                    color:"white"
                    font.pixelSize: 32
                    //                    anchors.centerIn: parent
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    function size(){
                        var size;
                        if(groupAddMainPage.isTransMessage){
                            return "("+groupManager.memberCount+")";
                        }
                        if(groupManager.isCreateGroup){
                            if(groupManager.memberCount===""){
                                size="";
                                return size;
                            }
                            else{
                                size="("+groupManager.memberCount+"/1000)";
                                return size;
                            }
                        }
                        else{
                            if(groupManager.memberCount===""){
                                size="("+memberManager.memberSize+"/1000)";
                                return size;
                            }
                            else{
                                size=groupManager.getSize("",memberManager.memberSize,groupManager.memberCount);
                                return size;
                            }
                        }
                    }
                }

            }
        }

        CTabView {
            id: myTabView

            anchors.top: titleBackground.bottom
            anchors.bottom: parent.bottom
            tabBar: CDoodTabViewEnterStyle{
                tabView: myTabView
                onTabClick: {
                    if(myTabView.currentIndex == 1){
                        enterpriseManager.getFarOrgs();
                    }
                }
            }
            CTab {
                title: qsTr("联系人")
                CDoodGroupAddMemberPage {
                    id: groupAddMemberPage

                    isTransMsg:groupAddMainPage.isTransMessage
                    anchors.fill: parent
                }
            }
            CTab {
                title: qsTr("组织架构")
                CDoodGroupAddOrgPage{
                    id: groupAddOrgPage

                    isTransMsg:groupAddMainPage.isTransMessage
                    anchors.fill: parent
                }
            }
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        //            indicatorDirection: Qt.Horizontal
        messageText: os.i18n.ctr(qsTr("正在操作中..."))
    }
}
