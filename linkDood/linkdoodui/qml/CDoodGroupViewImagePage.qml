import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtDocGallery 5.0
import com.syberos.multimedia.photos 2.0

CPage {
    id: groupSelectLocalImgePage

    property int maxSelectCount: 5
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupSelectLocalImgePage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupSelectLocalImgePage.statusBarHoldEnabled)
            groupSelectLocalImgePage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: groupManager
        onUploadGroupAvatarResult: {
            loadingDialog.hide();
            gToast.requestToast("群头像设置成功","","");
            pageStack.pop();
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: selectLocalImgeBackground
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
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("选择图片")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }
        CEditGridView {
            id: gridView

            anchors.top: titleBackground.bottom
            anchors.bottom: parent.bottom
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            cellHeight: parent.width/3
            cellWidth: cellHeight
            editable: false
            clip:true
            model: gallery

            Rectangle{
                z:parent.z -1
                anchors.fill:parent
                color:"black"
            }
            DocumentGalleryModel {
                id: gallery

                autoUpdate: true
                rootType: DocumentGalleryModel.Image
                sortProperties: ["-lastModified"]
                properties: ["fileExtension", "fileName", "filePath", "fileSize", "lastModified", "lastAccessed", "mimeType", "path", "url"]
            }

            delegate: CEditGridViewDelegate {
                id: gridviewDelegate
                width: gridView.cellHeight -6
                height: width
                editView: gridView
                singleShotted:true
                anchors.margins: 3
                editLabelSize:Qt.size(0,0)
                onClicked: {
//                      pageStack.replace(Qt.resolvedUrl("qrc:/qml/CDoodHeaderImageCropPage.qml"), {iconSource:url}, true);
                    groupManager.uploadGroupAvatar(filePath)
                    loadingDialog.show();

//                    console.log("xxxxxxxxx:"+filePath)
//                   var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodHeaderImageCropPage.qml"),"CDoodHeaderImageCropPage");
//                    pageStack.push(component,{iconSource:url});
                }

                Rectangle{
                    z:parent.z -1
                    anchors.fill:parent
                    color:"black"
                    radius: 6
                    border.color: "#DCDCDC"
                    border.width: 1

                 //   opacity: 0.5

                }

                PImage {
                    id: imageImage

                    //                    width: gridView.cellHeight
                    //                    height: width
                    sourceUrl: url
                    animated: false
                    thumbnailOnly: false
                    anchors.centerIn: parent
                    z:parent.z- 1
                    visible: false
                    onSourceUrlChanged:{
                        if(sourceUrl !=""){
                            icon.source = imageImage.sourceUrl
                        }
                    }
                }
                Image {
                    id: icon

                    sourceSize: Qt.size(gridviewDelegate.width-6,gridviewDelegate.width-6)
                    clip:true
                    z:parent.z+1
                    asynchronous: true
                    source: "qrc:/res/chat_tool_photo_normal.png"
                    anchors.centerIn: parent
                    onSourceChanged: {
                        console.log("1:"+icon.source)
                    }
                }
            }

        }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在上传头像中..."))
    }
}
