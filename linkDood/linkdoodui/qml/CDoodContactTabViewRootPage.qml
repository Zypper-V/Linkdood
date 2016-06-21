import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: contactTabViewPage

    property Component enterpriceRootPageCompoent: CDoodEnterpriseRootPage{
        anchors.fill: parent
    }

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            contactTabViewPage.statusBarHoldItemColor = rootTabViewBackground.color

            contactTabViewPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(contactTabViewPage.statusBarHoldEnabled)
            contactTabViewPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        } else if (status === CPageStatus.Show) {
        }
    }

//    Connections {
//        target: chatManager

//        onSendShowChatPage: {
//            console.log("CDoodRootTabbView  onSendShowChatPage !!!")
//            showChatPage(chatName, targetid, chatType, icon)
//            tabView.currentIndex = 0;
//        }
//    }

//    function showChatPage(chatName, targetid, chatType, icon) {
//        console.log("CDoodRootTabbView  showChatPage !!!")

//        pageStack.pop(contactTabViewPage, true)

//        var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodChatPage.qml"),"CDoodChatPage");

//        pageStack.push(component,
//                       {  chatName : chatName,
//                           targetid: targetid,
//                           chatType: chatType,
//                           icon: icon
//                       });
//        component.initMessage();
//    }

    contentAreaItem: Item {
        Rectangle {
            id: rootTabViewBackground
            anchors.top: parent.top
            anchors.bottom: tabView.top
            width:parent.width
            color: "#1c1b21"
            z:parent.z-1
        }

        CTabView {
            id:tabView
            tabPosition : Qt.Qt.TopEdge

            tabBar: Row {
                anchors.bottom: parent.bottom
                height: 160
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

                title: os.i18n.ctr(qsTr("联系人"))

                CDoodEnterpriseRootPage {
                    id: contactRootPage
                    anchors.fill: parent
                }
            }

            CTab {
                id:contactRootTab
                property url imgSource: "qrc:/res/icon-contact.png"
                property url imgActiveSource: "qrc:/res/icon-contact-h.png"
                property bool newMessage: false

                title: os.i18n.ctr(qsTr("组织架构"))

                Loader {
                    anchors.fill: parent
                    asynchronous: false
                    sourceComponent: enterpriceRootPageCompoent
                }
            }
        }
    }

    Component.onCompleted: {

    }
}
