import QtQuick 2.0
import com.syberos.basewidgets 2.0
CPage {
    id:imagePreView
    property string iconSource

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            imagePreView.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(imagePreView.statusBarHoldEnabled)
            imagePreView.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
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
//                        pageStack.push()
                    }
                }
                Text{
                    text:qsTr("预览")
                    color:"white"
                    font.pixelSize: 36
                    anchors.centerIn: parent
                }
                Rectangle{
                    id: uploadheader
                    width:120
                    height: 60
                    color: "green"
                    radius: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10

                    Text{
                        text:qsTr("确定")
                        font.pixelSize: 28
                        color:"white"
                        anchors.centerIn: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                        if(flick.moving == false &&
                          (thePinchArea.selectedAreaX + thePinchArea.selectedWidth < forSaveCanvas.width) &&
                          (thePinchArea.selectedAreaY + thePinchArea.selectedHeight < forSaveCanvas.height))
                        {
                            forSaveCanvas.imagedata = 1
                            forSaveCanvas.requestPaint()
                            source.visible = false
                            userProfileManager.uploadAvatar(forSaveCanvas.filePath)
                            pageStack.pop();
                        }
                        }
                    }

                }
            }
            Rectangle{
                id:imageArea
                color: "black"
                anchors.top: titleBackground.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                Flickable{
                    id:flick
                    anchors.fill: parent
                    contentWidth: source.width
                    contentHeight: source.height
                    property real preContentX: 0
                    property real preContentY: 0
                    onMovementEnded: {
                        thePinchArea.selectedAreaX = (thePinchArea.initAreaX + contentX) /
                                                     thePinchArea.globalScale
                        thePinchArea.selectedAreaY = (thePinchArea.initAreaY + contentY) /
                                                     thePinchArea.globalScale
                        console.log("current selectedAreaX: " + thePinchArea.selectedAreaX)
                        console.log("current selectedAreaY: " + thePinchArea.selectedAreaY)
                        console.log("current selectedAreaWidth: " + thePinchArea.selectedWidth)
                        console.log("current selectedAreaHeight: " + thePinchArea.selectedHeight)
                        console.log("image width" + source.width)
                        console.log("image height" + source.height)
                    }
                        Image {
                            id: source
                            width: imageArea.width
                            height: width / refImg.ratio
                            source: iconSource
                        }
                        Image {
                            id: refImg
                            visible: false
                            property real ratio: width / height
                            source: iconSource
                        }
                    PinchArea{
                        id: thePinchArea
                        width: Math.max(flick.contentWidth, flick.width)
                        height: Math.max(flick.contentHeight,flick.height)
                        anchors.centerIn: parent
                        pinch.minimumScale: 0.2
                        pinch.maximumScale: 1.4

                        property real initAreaX: 20
                        property real initAreaY: 250

                        property real selectedAreaX: 20
                        property real selectedAreaY: 250
                        property real selectedWidth: imageArea.width - 40
                        property real selectedHeight: selectedWidth
                        property real globalScale: 1
                        onPinchUpdated: {
                            if(  ((source.width < forSaveCanvas.framWidth) && pinch.scale < 1)  ||
                                 ((source.height < forSaveCanvas.framHeight) && pinch.scale < 1) ||
                                 ((source.width >  forSaveCanvas.framWidth * 5)  && pinch.scale > 1) ||
                                 ((source.height>  forSaveCanvas.framHeight * 5)  && pinch.scale > 1)
                                    )  return
                            globalScale *= pinch.scale
                            source.width *= pinch.scale
                            source.height *= pinch.scale
                            selectedWidth /= pinch.scale
                            selectedHeight /= pinch.scale
                            selectedAreaX = (initAreaX + flick.contentX) / globalScale
                            selectedAreaY = (initAreaY + flick.contentY) / globalScale
                            console.log("current selectedAreaX: " + thePinchArea.selectedAreaX)
                            console.log("current selectedAreaY: " + thePinchArea.selectedAreaY)
                            console.log("current selectedAreaWidth: " + thePinchArea.selectedWidth)
                            console.log("current selectedAreaHeight: " + thePinchArea.selectedHeight)
                            console.log("image width" + source.width)
                            console.log("image height" + source.height)
                        }
                        onPinchFinished: {
                        }
                    }
                }
                Canvas{
                    id:forSaveCanvas
                    anchors.top:parent.top
                    anchors.left:parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    property real framX: 20
                    property real framY: 250
                    property real framWidth: imageArea.width - 40
                    property real framHeight: framWidth
                    property var imagedata: null
                    property real imgX: 0
                    property real imgY: 0
                    property real imgWidth: 0
                    property real imgHeight: 0
                    property string filePath: "/home/user/data.jpg"
                    Image {
                        property real initScale: width / refImg.width
                        id: forSaveSource
                        width: imageArea.width
                        height: width / refImg.ratio
                        visible: false
                        source: iconSource
                    }
                    onPaint: {
                        var ctx = getContext("2d")
                        if(imagedata != null){
//                            anchors.top = parent.top + 250
//                            anchors.left = parent.left + 20
//                            anchors.right = parent.right - framX
//                            anchors.bottom = top +
                            anchors.topMargin = 250
                            anchors.leftMargin = 20
                            width = framWidth
                            height = width
                            imgX = thePinchArea.selectedAreaX / forSaveSource.initScale
                            imgY = thePinchArea.selectedAreaY / forSaveSource.initScale
                            imgWidth = thePinchArea.selectedWidth / forSaveSource.initScale
                            imgHeight = thePinchArea.selectedHeight / forSaveSource.initScale
                            console.log("imgX " + imgX)
                            console.log("imgY " + imgY)
                            console.log("imgWidth " + imgWidth)
                            console.log("imgHeight" + imgHeight)
                            ctx.drawImage(forSaveSource, imgX, imgY, imgWidth, imgHeight,
                                          0, 0, width, height)
//                            forSaveCanvas.visible = false
                            console.log(" width " + width + " height " + height)
                            forSaveCanvas.save(filePath)
                        }
                        else{
                            ctx.fillStyle = "#a0000000"
                            ctx.beginPath()
                            ctx.rect(0, 0, parent.width, framY)
                            ctx.rect(0, framY, 20, framY + framHeight)
                            ctx.rect(parent.width - 20, framY, parent.width, framY + framHeight)
                            ctx.rect(0, framY + framHeight, parent.height, parent.height)
                            ctx.fill()
                        }

                    }
                }
            }
        }
    }
}
