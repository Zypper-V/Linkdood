import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupAddMainPage
    anchors.fill: parent
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupAddMainPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupAddMainPage.statusBarHoldEnabled)
            groupAddMainPage.statusBarHoldItemColor = "#edf0f0"
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
                    contactManager.clearMember();
                    enterpriseManager.clearMember();
                    groupManager.clearMemberCount();
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
                anchors.rightMargin: 5
                width: 120
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
                    text:groupManager.memberCount===""?qsTr("确定"):qsTr("确定(")+groupManager.memberCount+qsTr(")")
                    color:"white"
                    font.pixelSize: 32
                    anchors.centerIn: parent
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

                    anchors.fill: parent
                }
            }
            CTab {
                title: qsTr("组织架构")
                CDoodGroupAddOrgPage{
                    id: groupAddOrgPage
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
