import QtQuick 2.0

MouseArea{
    id:button

    property string pressedIcon: "qrc:/res/main_title_back_button_press.png"
    property string normalIcon: "qrc:/res/main_title_back_button.png"

    implicitWidth:icon.width
    implicitHeight: icon.height

    Image {
        id: icon

        source: normalIcon
        anchors.centerIn: parent
    }
    onPressed: icon.source =  pressedIcon;
    onReleased: icon.source =  normalIcon;
}
