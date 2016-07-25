import QtQuick 2.0

MouseArea{
    id:button

    property string pressedIcon: "qrc:/res/main_title_back_button_press.png"
    property string normalIcon: "qrc:/res/main_title_back_button.png"
    property bool   bNormalBtn: false
    property string text: ""
    property alias  iconImag: icon

    implicitWidth:icon.width
    implicitHeight: icon.height

    Image {
        id: icon
        source: normalIcon
    }
    Text{
        id:textId
        text:button.text
        color:"white"
        font.pixelSize: 32
        visible: bNormalBtn

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: icon.right
        anchors.leftMargin: 20
    }

    onPressed: icon.source =  bNormalBtn ? normalIcon: pressedIcon;
    onReleased: icon.source =  normalIcon;
    Component.onCompleted: {
        if(!button.bNormalBtn){
            icon.anchors.centerIn = parent
        }else{
            icon.anchors.left= parent.left
            icon.anchors.leftMargin= 20
            icon.anchors.verticalCenter= textId.verticalCenter
        }
    }
}
