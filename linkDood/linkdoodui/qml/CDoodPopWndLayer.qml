import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item{
    id:root

    property bool  canceledOnBackKeyReleased :false
    property color contentItemBackGroundColor: "black"
    property var   contentItemBackGroundOpacity: 0.73
    signal backKeyReleased()
    signal outAreaClicked()

    property Item contentItem: null

    property bool isLayoutParentCenter: true

    parent: gAppUtils.pageStackWindow.contentRoot
    z:1000
    visible: false

    function show(){
        root.visible = true;
    }

    function hide(){
        root.visible = false;
    }

    anchors.fill: parent
    Rectangle{
        id:background

        anchors.fill: parent
        color:contentItemBackGroundColor
        opacity: contentItemBackGroundOpacity
        z:parent.z - 1
    }
    /*! 点击返回键触发hide()请求。 */
    Keys.onReleased:{
        if (event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
            event.accepted = true
            if(!canceledOnBackKeyReleased) {
                backKeyReleased()
            } else {

            }
        }/*! end of if ( event) */
    }
    onVisibleChanged: {
        if(!visible){
            gAppUtils.popDialog(root)
            if(gAppUtils.dialogWaitToShow()){
                gAppUtils.lastDialog().show()
            }
        }else{
            if(gAppUtils.lastDialog() !== root){
                gAppUtils.pushDialog(root)
            }
            focus = true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            outAreaClicked()
        }
    }

    Component.onDestruction: {
        visible = false
        gAppUtils.popDialog(root)
    }
    Component.onCompleted: {
        if(contentItem){
            contentItem.parent = root;
            contentItem.z = root.z+1;
            if(isLayoutParentCenter){
                contentItem.anchors.centerIn = root;
            }
        }
    }
}
