import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: fileViewPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            fileViewPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(fileViewPage.statusBarHoldEnabled)
            fileViewPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: sysMsgBackground
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
                    fileViewManager.reset();
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("下载预览")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }
        Rectangle{
            id:bottomBackground
            color:"#003953"
            width:parent.width
            height:80
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            Text{
                id:fileStatus
                text: setText()
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent

                function  setText(){
                    if(fileViewManager.status === 1){
                        return qsTr("下载");
                    }else if(fileViewManager.status === 2){
                        return qsTr("下载中...");
                    }else if(fileViewManager.status === 3){
                        return qsTr("打开");
                    }
                }
            }
            //TODO:replace following a button to MouseArea
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(fileViewManager.status === 3){
                        fileViewManager.openFile();
                        console.log("file:"+fileViewManager.path)
                         fileOpen.open("file://" + fileViewManager.path, CMIMEDialogTool.Open,"image/jpg")
                    }else if(fileViewManager.status === 1){
                        fileViewManager.downloadFile();
                    }else if(fileViewManager.status === 2){
                        //
                    }
                }
            }
        }
        Rectangle{
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottomBackground.top
            color:"#F2F2F2"

            Image {
                id: fileIcon
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -200
                width: 320
                height: 320
//                sourceSize: Qt.size(640,640);
                source: chatManager.judgeFileFromat(fileViewManager.fileName)
            }
            Text {
                id: fileName
                font.pixelSize: 30
                anchors.top: parent.bottom
                anchors.topMargin: 40
                anchors.centerIn: parent
                width: parent.width - 200
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
                text: fileViewManager.fileName
            }
            CProgressBar {
                id:loadStatus

                minimum: 0
                maximum: 100
                width: parent.width - 20
                height: 8
                visible:fileViewManager.status===2
                value: fileViewManager.proggress+10

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 200
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        CMIMEDialog{
            id:fileOpen

        }
    }
}
