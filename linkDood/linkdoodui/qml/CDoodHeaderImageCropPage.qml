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
                IconButton{
                    id: uploadheader
                    anchors.right: parent.right
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if(flick.moving == false &&
                          (thePinchArea.selectedAreaX + thePinchArea.selectedWidth < forSaveCanvas.width) &&
                          (thePinchArea.selectedAreaY + thePinchArea.selectedHeight < forSaveCanvas.height))
                        {
                            forSaveCanvas.imagedata = 1
                            forSaveCanvas.requestPaint()
                            source.visible = false
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
//                        thePinchArea.selectedAreaX += (flick.contentX - flick.preContentX)
//                        thePinchArea.selectedAreaY += (flick.contentY - flick.preContentY)
                        thePinchArea.selectedAreaX = (thePinchArea.initAreaX + contentX) /
                                                     thePinchArea.globalScale
                        thePinchArea.selectedAreaY = (thePinchArea.initAreaY + contentY) /
                                                     thePinchArea.globalScale
//                        console.log("current selectedAreaX: " + thePinchArea.selectedAreaX)
//                        console.log("current selectedAreaY: " + thePinchArea.selectedAreaY)
//                        console.log("current selectedAreaWidth: " + thePinchArea.selectedWidth)
//                        console.log("current selectedAreaHeight: " + thePinchArea.selectedHeight)
//                        flick.preContentX = flick.contentX
//                        flick.preContentY = flick.contentY
                    }
                        Image {
                            id: source
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
                                 ((source.width >  forSaveCanvas.framWidth * 10 )  && pinch.scale > 1) ||
                                 ((source.height>  forSaveCanvas.framHeight * 10 )  && pinch.scale > 1)
                                    )  return
                            globalScale *= pinch.scale
                            source.width *= pinch.scale
                            source.height *= pinch.scale
                            selectedWidth /= pinch.scale
                            selectedHeight /= pinch.scale
                            selectedAreaX = (initAreaX + flick.contentX) / globalScale
                            selectedAreaY = (initAreaY + flick.contentY) / globalScale
//                            selectedAreaX = (selectedAreaX + (flick.contentX - flick.preContentX)) / pinch.scale
//                            selectedAreaY = (selectedAreaY + (flick.contentY - flick.preContentY)) / pinch.scale
//                            flick.preContentX = flick.contentX
//                            flick.preContentY = flick.contentY
                            console.log("current selectedAreaX: " + thePinchArea.selectedAreaX)
                            console.log("current selectedAreaY: " + thePinchArea.selectedAreaY)
                            console.log("current selectedAreaWidth: " + thePinchArea.selectedWidth)
                            console.log("current selectedAreaHeight: " + thePinchArea.selectedHeight)
                        }
                        onPinchFinished: {
//                            thePinchArea.selectedAreaX += flick.contentX - flick.preContentX
//                            thePinchArea.selectedAreaY += flick.contentY - flick.preContentY
//                            flick.preContentX = flick.contentX
//                            flick.preContentY = flick.contentY
                        }
                    }
                }
                Canvas{
                    id:forSaveCanvas
                    anchors.fill: parent
                    property real framX: 20
                    property real framY: 250
                    property real framWidth: imageArea.width - 40
                    property real framHeight: framWidth
                    property var imagedata: null
                    Image {
                        id: forSaveSource
                        visible: false
                        source: iconSource
                    }
                    onPaint: {
                        var ctx = getContext("2d")
                        if(imagedata != null){
                            ctx.drawImage(forSaveSource, thePinchArea.selectedAreaX, thePinchArea.selectedAreaY,
                                          thePinchArea.selectedWidth, thePinchArea.selectedHeight,
                                          framX, framY, framWidth, framHeight)
//                            console.log("source width: " + forSaveSource.width)
                        }
                        ctx.fillStyle = "#a0000000"
                        ctx.beginPath()
                        ctx.rect(0, 0, parent.width, framY)
                        ctx.rect(0, framY, 20, framY + framHeight)
                        ctx.rect(parent.width - 20, framY, parent.width, framY + framHeight)
                        ctx.rect(0, framY + framHeight, parent.height, parent.height)
                        ctx.fill()
                    }
                }
                 //TODO: call function forSaveCanvas.context.getImage(forSaveSource,ramX, framY, framWidth, framHeight)
                 //to get the new Header Image
            }
        }
    }
}
