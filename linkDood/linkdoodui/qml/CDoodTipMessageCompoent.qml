import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id:tipMessageCompoent

    Item {
        id: tipMessageCompoentRoot

        signal showMenu
        width: chatListView.width
        height: tipMessage.height
        Rectangle{
            id:tipMessage
            color:"#ced1d1"

            anchors.centerIn: parent
            width:tipText.width+20
            height: tipText.height+20
            radius: 6
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    emit: showMenu();
                }
            }

            CLabel{
                id:tipText

                color:"white"
                font.pixelSize: 28
                text:model.modelData.body
                height: 30 * lineCount
                width: tipMessage.setWidth()
                wrapMode: TextInput.WrapAnywhere
                clip:true
                anchors.centerIn: parent
            }
            function setWidth(){
                console.log("tip width:"+tipText.implicitWidth+"content:"+model.modelData.body)
                if(tipText.implicitWidth >(chatListView.width-80)){
                    return chatListView.width-80;
                }else{
                    return tipText.implicitWidth;
                }
            }
        }

    }
}
