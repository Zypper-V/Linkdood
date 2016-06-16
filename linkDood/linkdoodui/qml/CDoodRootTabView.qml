import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: rootTabViewPage
    anchors.fill: parent

    property Component contactRootPageCompoent: CDoodContactRootPage {
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
            tabPosition : Qt.BottomEdge

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
        }
    }

    Component.onCompleted: {

    }
}
