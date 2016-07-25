import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id:tipMessageCompoent

    Item {
        id: tipMessageCompoentRoot

        width: chatListView.editing ? chatListView.width - 100 : chatListView.width
        height: tipMessage.height
        Rectangle{
            id:tipMessage
            color:"#DCDCDC"

            anchors.centerIn: parent
            width:tipText.width+20
            height: tipText.height+20
            radius: 10
            CLabel{
                id:tipText

                color:"white"
                font.pixelSize: 20
                text:model.modelData.body

                anchors.centerIn: parent
            }
        }
    }
}
