import QtQuick 2.0
import com.syberos.basewidgets 2.0
CPage {
    id:imagePreView
    property string  imageSource
    property string  url
    property string  tip
    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            imagePreView.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(imagePreView.statusBarHoldEnabled)
            imagePreView.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: chatManager
        onDownloadMainImageResult:{
            imagePreView.tip="";
            if(imagePreView.url==main_url && chatManagerModel.fileExistAtLocal(localpath)){
                imagePreView.imageSource="file://"+localpath;
            }
        }
    }

    contentAreaItem:Item {
        anchors.fill: parent

        Rectangle{
            id: pagebackground
            anchors.fill: parent
            color: "black"

            Rectangle{
                id: titleBackground

                color:"#003953"
                width:parent.width
                height:86
                z:100
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
                    text:qsTr("预览")+imagePreView.tip
                    color:"white"
                    font.pixelSize: 36
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id:imageArea
                color: "black"
                anchors.top: titleBackground.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                focus: true
                Flickable{
                    id:flick
                    width: Math.min(parent.width, img.width)
                    height:Math.min(parent.height, img.height)
                    contentWidth: img.width
                    contentHeight: img.height
                    contentItem.y: (imageArea.height - height) / 2
                    contentItem.x: (imageArea.width - width) / 2
                    Image {
                        id: img
//                        width: imageArea.width
//                        height: width / refRetio.retio
                        width:chatManagerModel.imageWidth(imageSource);
                        height:chatManagerModel.imageHeight(imageSource);
                        source:imageSource
                        MouseArea{
                            anchors.fill: parent
                        }
//                        onSourceChanged: {
//                            img.width = chatManagerModel.imageWidth(imageSource);
//                            img.height = chatManagerModel.imageHeight(imageSource);
//                            console.log("view image w:"+img.width+",h:"+img.height);
//                        }
                    }
                    PinchArea{
                        id: thePinchArea
                        pinch.minimumScale:0.5
                        anchors.fill: parent
                        pinch.maximumScale:2.0
                        pinch.target: imageArea
//                        onPinchUpdated: {

//                            if((img.width <= imageArea.width * 3 || pinch.scale < 1) &&
//                                    (img.width >= imageArea.width || pinch.scale > 1)
//                                    ) {
//                                //                     //          globalScale *= pinch.scale
//                                img.width *= pinch.scale
//                                img.height *= pinch.scale
//                            }
//                        }
//                        onPinchStarted: {
//                            img.width = imageArea.width
//                            img.height = img.width / refRetio.retio
//                        }

//                        onPinchFinished: {

//                            img.width = imageArea.width
//                            img.height = img.width / refRetio.retio
//                            if(img.width <imageArea.width){
//                                img.width = imageArea.width
//                                img.height = img.width / refRetio.retio
//                            }
//                        }
                    }
                }

//                Image{
//                    id: refRetio
//                    property real retio: sourceSize.width / sourceSize.height
//                    visible: false
//                    source:imageSource
//                    onSourceChanged: {
//                        refRetio.retio = sourceSize.width / sourceSize.height;
//                    }
//                }
            }
        }
    }
}
