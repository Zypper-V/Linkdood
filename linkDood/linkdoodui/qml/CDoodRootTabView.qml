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
            showChatPage(chatName, targetid, chatType, icon)
            tabView.currentIndex = 0;
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
        component.initMessage();
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
                font.pixelSize: 36

                anchors.left: parent.left
                anchors.leftMargin: 21
                anchors.verticalCenter: parent.verticalCenter
            }

            Text{
                color: "white"
                text:"["+userProfileManager.name+"]"
                font.pixelSize: 20

                anchors.left: logo.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 8
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
                console.log("zhangp onCurrentIndexChanged currentIndex = ", currentIndex)

            }

            CTab {
                id:sessionListTab
                property url imgSource: "qrc:/res/icon-message.png"
                property url imgActiveSource: "qrc:/res/icon-message-h.png"
                property bool newMessage: false

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
}
