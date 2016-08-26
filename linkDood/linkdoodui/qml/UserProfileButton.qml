import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:comp
    
    property string leftText: ""
    property string rightImg: ""
    property string rigthText: ""
    property bool showLine:true
    property bool editable:false
    property int  rightTextMaxLen: 460
    signal clicked()

    radius: 10
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
        visible: rightImg !=""
        headerColor: "transparent"
        iconSource: setIcon("1",comp.rightImg)
        anchors{
            right: arrowTip.left
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
    }
    Text {
        id:rigthText
        
        text:comp.rigthText
        font.pixelSize: 22
        width:300
        elide: Text.ElideRight
        clip:true
        maximumLineCount: 1
        horizontalAlignment:Text.AlignRight
        onTextChanged: {
            console.log("text changed:"+text);
            rigthText.width = setWidth();
        }

        anchors{
            right: arrowTip.left
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
        function setWidth(){
            var tmp = rigthText.contentWidth+10;
            console.log("len:"+tmp);
            if(tmp>rightTextMaxLen){
                return rightTextMaxLen;
            }else if(tmp <300){
                return 300;
            }else{
                return tmp;
            }
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
//        color:"#777777"
        anchors.left:parent.left
       anchors.right: parent.right
       anchors.leftMargin: 30
       anchors.rightMargin: 30
    }
    MouseArea{
        anchors.fill: parent
        onPressed: parent.color = "#cdcdcd"
        onReleased: parent.color = "white"
        onCanceled: parent.color = "white"
        onClicked: {
            emit: comp.clicked();
        }
    }
}
