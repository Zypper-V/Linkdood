import QtQuick 2.0
import com.syberos.basewidgets 2.0
CDoodPopWndLayer{
    id:menu

    property string id: ""
    property int    index:-1
    property bool   isVisibleCopy :false

    onIsVisibleCopyChanged: {
        backItem.height = isVisibleCopy ? 330:230;
    }

    contentItemBackGroundOpacity:0.73
    contentItem:Rectangle{
        id:backItem

        color: "white"
        radius: 10
        width: 389
        height: 230
        anchors.centerIn: parent
        UserProfileButton{
            id:btnCopy

            width:parent.width
            height: 100
            leftText: qsTr("复制")
            radius: 4
            visible: isVisibleCopy

            anchors.top:parent.top
            anchors.topMargin: 10

            onClicked: {

                index = 0;
                inerClicked();
            }
        }
        UserProfileButton{
            id:btnDel

            width:parent.width
            height: 100
            leftText: qsTr("删除") ;
            radius: 4
            anchors.top:isVisibleCopy ? btnCopy.bottom :parent.top
            anchors.topMargin: 10
            onClicked: {

                index = 1;
                inerClicked();
            }
        }
        UserProfileButton{
            id:btnRepost

            width:parent.width
            height:100
            leftText: qsTr("转发") ;
            radius: 4
            showLine:false

            anchors.top: btnDel.bottom
            anchors.topMargin: 10
            onClicked: {
                index = 2;
                inerClicked();
                //pageStack.replace(Qt.resolvedUrl("qrc:/qml/CDoodGroupAddMemberPage.qml"), {state:"forwordMsg" }, true);
            }
        }
        //        UserProfileButton{
        //            id:btnMore

        //            width:parent.width
        //            height:100
        //            leftText: qsTr("更多") ;
        //            radius: 4
        //            showLine:false

        //            anchors.top: btnRepost.bottom
        //            anchors.topMargin: 10
        //            onClicked: {
        //                menu.hide();
        //            }
        //        }
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
