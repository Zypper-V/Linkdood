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
                    if(fileViewManager.status ===2){
                        alertDialog.show();
                    }
                    else{
                        fileViewManager.reset();
                        pageStack.pop();
                    }
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
                        openTextFile(fileViewManager.path,fileViewManager.fileName);
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
                width: parent.width - 100
                height: 8
                visible:fileViewManager.status===2
                value: fileViewManager.proggress+10

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 300
                anchors.left: parent.left
                anchors.leftMargin: 20
            }
            Image {
                id: btnCancel
                source: "qrc:/res/control/delete_btn.png"
                visible: loadStatus.visible

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 280
                anchors.left: loadStatus.right
                anchors.leftMargin: 10
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        fileViewManager.cancelDownload();
                    }
                }
            }
        }
        CDialog {
            id: alertDialog

            titleText: qsTr("提示")
            messageText: qsTr("文件正在下载，返回后将停止下载，您确定要返回吗？")
            onAccepted: {
                fileViewManager.cancelDownload();
                fileViewManager.reset();
                pageStack.pop();
            }
            onCanceled: {
            }
        }
    }
    function openTextFile(filepath, filename) {
        var mimeType = fileViewManager.getMimeType(filepath);
        var tmp = ""+mimeType;
        var isImage = tmp.search("image/");

        console.log("mimeType:"+mimeType+"isImage:"+isImage)
        if(mimeType === "text/plain"){
            pageStack.push("qrc:/CDoodTextViewer.qml", { fullfilepath: filepath ,
                                               fileName: filename })
        }else if(isImage !== -1){
            var myChatPage = pageStack.getCachedPage(Qt.resolvedUrl("CDoodViewImage.qml"),"CDoodViewImage");
            myChatPage.imageSource = "file://"+filepath;
            pageStack.push(myChatPage);
        }else{
            var comp = Qt.createComponent("qrc:/qml/CDoodMimePage.qml");
            if (comp.status === Component.Ready) {
                var mimeDialog = comp.createObject(fileViewPage);
            }
            var ret = mimeDialog.open(filepath, CMIMEDialogTool.View,mimeType)
            if(!ret){
                gToast.requestToast("不支持打开此类型文件("+filepath+")","","");
            }
        }
    }
}
