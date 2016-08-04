import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: rootTabViewPage

    property Component contactRootPageCompoent: CDoodContactMainPage {
        anchors.fill: parent
    }

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            rootTabViewPage.statusBarHoldItemColor = rootTabViewBackground.color

            rootTabViewPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(rootTabViewPage.statusBarHoldEnabled)
            rootTabViewPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        } else if (status === CPageStatus.Show) {
        }
    }

    Connections {
        target: chatManager

        onSendShowChatPage: {
            console.log("CDoodRootTabbView  onSendShowChatPage !!!")
            showChatPage(chatName, targetid, chatType, "")
            tabView.currentIndex = 0;
        }
    }
    Connections {
        target: loginManager

        onElsewhereLogin: {
            console.log("CDoodRootTabbView  onElsewhereLogin !!!")
            gToast.requestToast(tip,"","");
            contactManager.clearChatList();
            sessionListManager.clearChatList();
            loginManager.setAppLoginStatus(0);
            pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
        }
    }

    function showChatPage(chatName, targetid, chatType, icon) {
        console.log("CDoodRootTabbView  showChatPage !!!")

        pageStack.pop(rootTabViewPage, true)

        var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodChatPage.qml"),"CDoodChatPage");

        pageStack.push(component,
                       {  chatName : chatName,
                           targetid: targetid,
                           chatType: chatType,
                           icon: icon
                       });
 //      chatManager.updateUnreadMsg();
    }

    contentAreaItem: Item {
        Rectangle {
            id: rootTabViewBackground

            anchors.top: parent.top
            color:"#003953"
            width:parent.width
            height:86
            Text{
                id:logo

                color: "white"
                text:qsTr("天工圆圆")
                font.pixelSize: 28

                anchors.left: parent.left
                anchors.leftMargin: 21
                anchors.verticalCenter: parent.verticalCenter
            }

            Text{
                color: "white"
                text:"["+userProfileManager.name+"]"
                font.pixelSize: 16

                anchors.left: logo.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 5
            }
            Text{
                anchors.verticalCenter: parent.verticalCenter
                anchors.right:parent.right
                anchors.rightMargin: 240
                color:"white"
                font.pixelSize: 28
                text:userProfileManager.connectFlag
            }
            IconButton{
                id:btnSearchContacts
                pressedIcon:"qrc:/res/main_title_seek_button_press.png"
                normalIcon:"qrc:/res/main_title_seek_button.png"
                anchors.right: btnAddContacts.left
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    searchContactpage.show();
//                    pageStack.push(Qt.resolvedUrl("qrc:/qml/CDoodLocalSearchPage.qml"));
                }
            }
            CDoodLocalSearchPage{
                id:searchContactpage
            }

            IconButton{
                id:btnAddContacts
                pressedIcon:"qrc:/res/main_title_tool_button_press.png"
                normalIcon:"qrc:/res/main_title_tool_button.png"
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    addContactMenu.show();
                }
            }
        }

        CTabView {
            id:tabView
            tabPosition : Qt.BottomEdge

            anchors.top: rootTabViewBackground.bottom
            anchors.bottom: parent.bottom

            width:parent.width
            tabBar: Row {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                height: 108
                Repeater {
                    delegate: CDoodTabViewStyle {
                        tabview: tabView
                        id: tabviewStyle
                        width: tabView.width / tabView.tabModel.count
                    }
                    model: tabView.tabModel
                }
            }

            onCurrentIndexChanged: {
               if(currentIndex == 2){
                   userProfileManager.getPrivateSetting();
                   console.log("very press");
               }
            }

            CTab {
                id:sessionListTab
                property url imgSource: "qrc:/res/icon-message.png"
                property url imgActiveSource: "qrc:/res/icon-message-h.png"
                property bool newMessage: sessionListManager.unreadCount>0

                title: os.i18n.ctr(qsTr("消息"))

                CDoodSessionListPage {
                    id: sessionRootPage
                    anchors.fill: parent
                }
            }

            CTab {
                id:contactRootTab
                property url imgSource: "qrc:/res/icon-contact.png"
                property url imgActiveSource: "qrc:/res/icon-contact-h.png"
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("联系人"))

                Loader {
                    anchors.fill: parent
                    asynchronous: false
                    sourceComponent: contactRootPageCompoent
                }
            }
            CTab {
                id:userListTab
                property url imgSource: "qrc:/res/tab_personal_normal.png"
                property url imgActiveSource: "qrc:/res/tab_personal_pressed.png"
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("我的"))

                CDoodProfileDataPage{
                    id: userRootPage
                    anchors.fill: parent
                }
            }
        }
    }

    Component.onCompleted: {

    }
    CDoodPopWndLayer{
        id:addContactMenu

        isLayoutParentCenter:false
        contentItemBackGroundColor:"transparent"
        contentItem:Rectangle{
            color:"#003953"
            width:300
            height: 180
            radius: 10

            anchors.top: parent.top
            anchors.topMargin: 140
            anchors.right: parent.right
            anchors.rightMargin: 5

            IconButton{
                id:startChatItem

                bNormalBtn:true
                width:parent.width
                height: (parent.height - line.height)/2
                normalIcon:"qrc:/res/iv_main_tool_bt01_2.png"
                text:qsTr("发起群聊")

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 20
                onClicked: {
                    //TODO
                    groupManager.setIsCreateGroup(true);
                    pageStack.push(Qt.resolvedUrl("CDoodGroupAddMainPage.qml"));
                }
            }
            CLine{
                id:line
                anchors.top: startChatItem.bottom
                width:parent.width - 4
                anchors.horizontalCenter: parent.horizontalCenter
            }
            IconButton{
                id:addContactItem

                bNormalBtn:true
                width:parent.width
                height: (parent.height - line.height)/2
                normalIcon:"qrc:/res/iv_main_tool_bt02_2.png"
                text:qsTr("添加联系人/群")

                anchors.top: line.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                onClicked: {
                    //TODO
                     addContactMenu.hide();
                     pageStack.push(Qt.resolvedUrl("CDoodAddContactPage.qml"));
                }
            }
        }
        onOutAreaClicked:{
            addContactMenu.hide();
        }
        onBackKeyReleased: {
            addContactMenu.hide();
        }
    }
}
