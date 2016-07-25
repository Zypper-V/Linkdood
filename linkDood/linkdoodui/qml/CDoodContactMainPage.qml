import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item {
    id: contactMainPage
    anchors.fill: parent

    CTabView {
        id: myTabView

        anchors.top: parent.top
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
            CDoodContactRootPage {
                 id: sessionRootPage

                 anchors.fill: parent
           }
        }
        CTab {
            title: qsTr("组织架构")
            CDoodEnterprise{
                id: enterprisePage
                anchors.fill: parent
            }
        }
    }
//    Rectangle {
//        id: rootTabViewBackground
//        anchors.top: contactRootTitleBar.bottom
//        anchors.bottom: tabView.top
//        width:parent.width
//        color: "#1c1b21"
//        z:parent.z-1
//    }

//    CTabView {
//        id:tabView
//        anchors.top: contactRootTitleBar.bottom
//        anchors.bottom: parent.bottom

//        width: parent.width

//        tabPosition : Qt.TopEdge
//        tabBar: Row {
//            id:tabBarLine

//            anchors.top: tabView.bottom
//            anchors.horizontalCenter: tabView.horizontalCenter
//            height: 90
//            Repeater {
//                delegate: CDoodTabViewEnterStyle {
//                    tabview: tabView
//                    id: tabviewStyle

//                   anchors.verticalCenter: parent.verticalCenter
//                    width: 179
//                    height: 53
//                }
//                model: tabView.tabModel
//            }
////            CLine{
////                anchors.bottomMargin: 2
////                //anchors.bottom: tabBar.bottom
////                width: parent.width
////            }
//        }
////        CLine{
////            anchors.bottomMargin: 2
////            anchors.bottom: tabBarLine.bottom
////            width: parent.width
////        }

//        onCurrentIndexChanged: {
//            console.log("zhangp onCurrentIndexChanged currentIndex = ", currentIndex)

//        }

//        CTab {
//            id:sessionListTab
//            anchors.fill: parent
//            property url imgSource: "qrc:/res/icon-message.png"
//            property url imgActiveSource: "qrc:/res/icon-message-h.png"
//            property bool newMessage: false

//            title: os.i18n.ctr(qsTr("联系人"))

////            CDoodContactRootPage {
////                id: sessionRootPage
////                anchors.fill: parent
////            }
//            Rectangle{
//                anchors.fill: parent
//                color:"red"
//            }
//        }

//        CTab {
//            id:contactRootTab
//            property url imgSource: "qrc:/res/icon-contact.png"
//            property url imgActiveSource: "qrc:/res/icon-contact-h.png"
//            property bool newMessage: false

//            title: os.i18n.ctr(qsTr("enter"))
//            Rectangle{
//                anchors.fill: parent
//                color:"red"
//            }

////            CDoodEnterprise{
////                id: enterprisePage
////                anchors.fill: parent
////            }

////            Loader {
////                anchors.fill: parent
////                asynchronous: false
////                sourceComponent: cDoodEnterpriseCompoent
////            }
//        }
//    }

    Component.onCompleted: {
        console.log("CDoodContactMainPage.qml Component.onCompleted---------------")

    }
}
