import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id: root
    color: "white"

    property int columns: 8
    property int rows: 4
    property int itemsPerPage: columns*rows
    property variant flow: GridView.TopToBottom

    CLine{
        id:line
        anchors.top:parent.top
    }

    GridView{
        id: grid

        width: parent.width
        height: parent.height
        anchors.fill: parent

        model: userEmojiManager
        cellHeight: grid.height/rows
        cellWidth: grid.width/columns
        clip: true
        snapMode: GridView.SnapToRow
        flow: root.flow


        delegate: _testComponent

        onMovementEnded: {
            if(flow === GridView.TopToBottom){
                _centerPageAnimationHorizontal.restart();
                grid.currentIndex = ((grid.width*Math.round(grid.contentX/grid.width))/grid.width)*itemsPerPage;
            console.log("move end:"+grid.currentIndex)
            }
        }
        NumberAnimation { id: _centerPageAnimationHorizontal; target: grid; property: "contentX"; to: (grid.width*Math.round(grid.contentX/grid.width)); duration: 250 }

    }

    Component{
        id: _testComponent
        Item{
            id: _item
            width: grid.cellWidth
            height: grid.cellHeight
            Rectangle{
                id: _rect
                width: grid.cellWidth - 5
                height: grid.cellHeight - 5
                color: "white"
                opacity: mouseCell.pressed ? 0.5: 1;

                anchors.centerIn: _item
                BorderImage {
                    id: img
                    source: model.modelData.path
                    width: 36
                    height: 36
                    anchors.centerIn: parent
                }
            }
            MouseArea{
                id:mouseCell

                anchors.fill: _item
                onClicked: {
                    grid.forceActiveFocus();
                    grid.currentIndex = index;
                    userEmojiManager.itemClicked(model.modelData.path);
                    console.log("ddddddddddddddddd:"+root.width +"h:"+root.height)
                }
            }
        }
    }

    Timer{
        id: debounce
        running: false; repeat: false; interval: 300
    }
}
