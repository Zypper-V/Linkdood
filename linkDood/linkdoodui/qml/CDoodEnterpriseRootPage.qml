import QtQuick 2.0
import com.syberos.basewidgets 2.0
Item{

  anchors.fill: parent
  CEditListView{
      id:departListView

      anchors.top:parent.top
      anchors.left: parent.left
      height:60
      width:parent.width
      model:departMedol

      orientation:ListView.Horizontal

      delegate:CEditListViewDelegate{
          width:180
          height: 60

          Rectangle{
              id:departBackground

              anchors.fill: parent
              Text{
                  anchors.centerIn: parent
                  text:depart
              }
          }

          Rectangle {
              id : departMousePressBackgroud

              anchors.fill: parent
              visible: false
              color: "#cdcdcd"
          }
          onPressedChanged:{
              if(departMousePressBackgroud.visible){
                  departBackground.color = "#ffffff"
                  departMousePressBackgroud.visible = false
              }else{
                  departBackground.color = "#cdcdcd"
                  departMousePressBackgroud.visible = true
              }
          }
      }
  }

  ListModel{
      id:departMedol
      ListElement{
          depart:"xx1"
      }
      ListElement{
          depart:"xx2"
      }
      ListElement{
          depart:"xx3"
      }
  }

  ListModel{
      id:memDodel
      ListElement{
          _name: "Orange"
          icon: ""
      }
      ListElement{
          _name: "Orange"
          icon: ""
      }
      ListElement{
          _name: "Orange"
          icon: ""
      }
      ListElement{
          _name: "Orange"
          icon: ""
      }
      ListElement{
          _name: "Orange"
          icon: ""
      }
      ListElement{
          _name: "Orange"
          icon: ""
      }
  }

  CEditListView {
      id: enterpriseMemListView

      anchors.top: departListView.bottom
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.bottom: parent.bottom

      editable:false
      clip: true
      model: memDodel

      editing: false

      delegate:CEditListViewDelegate {
          id:contactListDelegate

          width: enterpriseMemListView.width
          height: 113
          onClicked: {

          }

          onPressedChanged:{
              if(mousePressBackgroud.visible){
                  background.color = "#ffffff"
                  mousePressBackgroud.visible = false
              }else{
                  background.color = "#cdcdcd"
                  mousePressBackgroud.visible = true
              }
          }

          Rectangle {
              width: contactListDelegate.width
              height: contactListDelegate.height


              Rectangle {
                  id : mousePressBackgroud
                  anchors.fill: parent
                  visible: false
                  color: "#cdcdcd"
              }

              Rectangle {
                  id : background
                  anchors.fill: parent
                  anchors.topMargin: 1
                  anchors.bottomMargin: 3
                  anchors.leftMargin: 2
                  anchors.rightMargin:  2

                  CDoodHeaderImage {
                      id: headPortraitImage
                      anchors.left: parent.left
                      anchors.leftMargin: 25
                      anchors.topMargin: 16
                      anchors.verticalCenter: parent.verticalCenter
                      width: 72
                      height: 72

                      name: _name/*sessionListManager.getSubName(model.modelData.name)*/
                      headerColor: "#efefef"/*sessionListManager.getHeaderColor(model.modelData.id)*/
                     // iconSource: "file://"+ model.modelData.thumbAvatar
                  }
                  Text {
                      id: nameText
                      anchors.left: headPortraitImage.right
                      anchors.leftMargin: 30
                      anchors.rightMargin: 20
                      anchors.top: parent.top
                      anchors.topMargin: 25
                      font.pixelSize: 32
                      height: 33
                      clip: true
                      color: "#333333"
                      verticalAlignment: Text.AlignVCenter
                      elide: Text.ElideRight
                      text: _name/*model.modelData.name*/
                  }
                  CLine {
                      width: parent.width
                      anchors.left: parent.left
                      anchors.leftMargin: 150
                      anchors.right: parent.right
                      anchors.bottom: parent.bottom
                      z: parent.z+2
                  }

              }
          }
      }
      CScrollDecorator{
          flickableItem: enterpriseMemListView
      }
  }
}
