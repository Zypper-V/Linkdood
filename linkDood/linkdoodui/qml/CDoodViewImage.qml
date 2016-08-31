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
        }else if(status === CPageStatus.Hide){
            thePinchArea.pinch.scale = 1.0
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
                    anchors.fill: parent
                    Image {
                        id: img
                        width:chatManagerModel.imageWidth(imageSource);
                        height:chatManagerModel.imageHeight(imageSource);
                        source:imageSource
                        anchors.centerIn: parent
                    }
                    PinchArea{
                        id: thePinchArea
                        pinch.minimumScale:0.2
                        anchors.fill: parent
                        pinch.maximumScale:20
                        pinch.target: img

                    }
                }
            }
        }
    }
}
