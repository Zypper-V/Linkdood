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
            console.log("123");
            if(imagePreView.url==main_url){
                console.log("234")
                imagePreView.tip="";
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
                        width: imageArea.width
                        height: width / refRetio.retio
                        source:imageSource
                        MouseArea{
                            anchors.fill: parent
                        }
                    }
                    PinchArea{
                        id: thePinchArea
                        pinch.minimumScale:0.7
                        anchors.fill: parent
                        pinch.maximumScale:1.3
                        pinch.target: imageArea
                        //   property real globalScale: 1
                        onPinchUpdated: {
                            if((img.width <= imageArea.width * 3 || pinch.scale < 1) &&
                                    (img.width >= imageArea.width || pinch.scale > 1)
                                    ) {
                                //                     //          globalScale *= pinch.scale
                                img.width *= pinch.scale
                                img.height *= pinch.scale
                            }
                            //                            if((img.height <= imageArea.height * 3 || pinch.scale < 1) &&
                            //                                (img.height >= imageArea.height || pinch.scale > 1)
                            //                                    ) {
                            ////                     //          globalScale *= pinch.scale
                            //                                img.width *= pinch.scale
                            //                                img.height *= pinch.scale
                            //                            }
                            //flick.contentItem.y = (imageArea.height - height) / 2
                            //flick.contentItem.x = (imageArea.width - width) / 2
                        }
                        onPinchStarted: {
                            img.width = imageArea.width
                            img.height = img.width / refRetio.retio
                        }

                        onPinchFinished: {
//                            if((img.width <= imageArea.width * 3 || pinch.scale < 1) &&
//                                    (img.width >= imageArea.width || pinch.scale > 1)
//                                    ) {
//                                //                     //          globalScale *= pinch.scale
//                                img.width *= pinch.scale
//                                img.height *= pinch.scale
//                            }
                            img.width = imageArea.width
                            img.height = img.width / refRetio.retio
                            if(img.width <imageArea.width){
                                img.width = imageArea.width
                                img.height = img.width / refRetio.retio
                            }

                            //                            if(img.height < imageArea.height){
                            //                                img.height = imageArea.height
                            //                                img.width = img.width / refRetio.retio
                            //                            }
                            //flick.contentItem.y = (imageArea.height - height) / 2
                            //flick.contentItem.x = (imageArea.width - width) / 2
                            //                            flick.returnToBounds()
                        }
                    }
                }

                Image{
                    id: refRetio
                    property real retio: sourceSize.width / sourceSize.height
                    visible: false
                    source:imageSource
                }
            }
        }
    }
}
