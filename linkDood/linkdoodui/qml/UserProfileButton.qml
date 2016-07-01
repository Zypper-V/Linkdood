import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:comp
    
    property string leftText: ""
    property string rightImg: ""
    property string rigthText: ""
    property bool showLine:true
    property bool editable:false
    
    signal clicked()

    radius: 0
    height: 100
    color: "white"

    anchors.topMargin: 2
    anchors.left: parent.left
    anchors.leftMargin: 2
    anchors.right: parent.right
    anchors.rightMargin: 2

    Text{
        id:leftTip
        
        text:leftText
        font.pixelSize: 32

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
    }
    CDoodHeaderImage {
        id: rightIcon

        width: 90
        height: 90
        radius: 10
        headerColor: "transparent"
        iconSource: comp.rightImg
        anchors{
            right: arrowTip.left
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
    }
    Text {
        id:rigthText
        
        text:comp.rigthText
        font.pixelSize: 32

        anchors{
            right: arrowTip.left
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
    }
    Image {
        id:arrowTip
        
        visible: comp.editable
        source: "qrc:/res/arrow_icon.png"
        anchors{
            right: parent.right
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
    }
    CLine{
        visible: comp.showLine
        anchors.bottom: parent.bottom
        color:"#777777"
    }
    MouseArea{
        anchors.fill: parent
        onPressed: parent.color = "#7c9dd9"
        onReleased: parent.color = "white"
        onClicked: {
            emit: comp.clicked();
        }
    }
}
