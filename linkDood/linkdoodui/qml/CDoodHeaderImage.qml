import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property url iconSource: ""
    property string name: ""
    property string headerColor: ""
    property int nameTextSize: root.height / 3
    property int radius: root.width / 2
    readonly property bool isDefaultImageShow: defaultImage.visible

    Rectangle {
        id: defaultImage
        anchors.fill: parent

        radius: defaultImage.width / 2
        color: headerColor

        Text {
            id: nameText
            anchors.centerIn: parent
            font.pixelSize: nameTextSize
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            font.bold: true
            text: name
        }
    }

    Item {
        id: roundImage
        anchors.fill: parent
        implicitWidth: src.implicitWidth
        implicitHeight: src.implicitHeight

        OpacityMask {
            id: bd
            anchors.fill: parent
            source: src.status === Image.Ready ? src : null
            maskSource:  Rectangle{
                width: roundImage.width
                height: roundImage.height
                radius: root.radius
                visible: false
            }
        }

        Image {
            id: src
            anchors.fill: parent
            visible: false

            sourceSize: Qt.size(src.width,src.height)
            asynchronous: true
            cache: true
            source: sessionListManager.checkFileExists(iconSource) ? iconSource : "qrc:/res/headerDefault.png"

            onStatusChanged: {
                if (src.status === Image.Error || src.status === Image.Null) {
                    roundImage.visible = false
                    defaultImage.visible = true
                } else if (src.status === Image.Ready) {
                    if (sessionListManager.checkFileExists(iconSource)) {
                        roundImage.visible = true
                        defaultImage.visible = false
                    } else {
                        roundImage.visible = false
                        defaultImage.visible = true
                    }
                }
            }
        }
    }
}
