import QtQuick 2.0
import com.syberos.basewidgets 2.0

CTabView{
    id:root

    anchors.fill: parent
    tabPosition : Qt.BottomEdge
    tabBar: Rectangle {

        height: 90
        color: "white"
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.margins: 0

        Row{
            height: root.height
            width: parent.width

            Repeater{
                model: root.tabModel
                delegate: Rectangle {
                    id: tabviewStyle
                    height: 90
                    width: height
                    opacity: 0.5
                    color:index === root.currentIndex? "#777777" : "white"
                    Image {
                        id: img
                        source: root.getTab(index).imgSource
                        anchors.centerIn: parent
                        height: 40
                        width:height
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            if(root.currentIndex != index)
                                root.currentIndex = index
                        }
                    }
                }
            }
        }
        CLine{
            anchors.top:parent.top
        }
    }
    CTab {
        id:basicTab
        width: 90
        height: width
        property url imgSource: "qrc:/res/smilies/instruct/weixiao.png"
        CDoodEmojiGridView{
            anchors.fill: parent
        }
    }
    CTab {
        id:gifTab
        width: 90
        height: width
        CDoodDyEmojiGridView{
            anchors.fill: parent
        }
        property url imgSource: "qrc:/res/smilies/dynamic_expression/Dynamic_Expression_01.gif"
    }
}
