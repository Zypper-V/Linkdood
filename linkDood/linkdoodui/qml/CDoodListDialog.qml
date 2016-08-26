import QtQuick 2.3
import com.syberos.basewidgets 2.0

CDialog {
    id: listDialog
    objectName: "CListDialog_SyberOS2.0"

    property int curIndex

    /*! 列表最大可见项目数量，其他项目滚动后可见。默认横屏4个，竖屏8个。 */
    property int maxVisibleItems: gScreenInfo.isPortrait ? 8 : 4

    /*! \internal */
    property alias delegateHeight: listDialog.itemHeight

    /*! 交互功能是否开启，即是否可以滑动、点击等。默认为true。 */
    property bool interactive: true

    /*! 是否可标记选中状态，默认为true。 */
    property bool itemCheckable:true

    /*! 列表的delegate组件，可使用CSelectListViewDelegate自定义。*/
    property Component itemDelegate: myDelegate

    /*!
        \qmlproperty Component CListDialog::selectLabelComponent
        选中项标记组件，可通过这个接口来自定义选中项标记的外观。
    */
    property Component selectLabelComponent: Image { source: "qrc:/res/control/checked.png" }

    /*! 项目之间是否互斥，即只能有一个可被选中，默认值为true。*/
    property bool itemExclusive: true

    /*! 项目字体大小 */
    property int itemFontSize: 30

    /*! 项目的高度 */
    property int itemHeight:110

    /*! 项目文本颜色 */
    property color itemTextColor:"#777777"

    /*! \internal */
    property int maxHeight: parent.height - 40 - 80

    /*! 列表项目显示的文本数组。 */
    property variant model

    /*!
        表示如果在互斥模式下是否可以存在没有选中的项目，即反选自己，默认可以的。
        如果可以反选，则可能在一个列表中没有一个是选中的，如果不可以反选自己，则至少有一个是选中的。
    */
    property bool reverseSelectOnExclusiveMode: false

    /*! 返回选中项目的个数*/
    function selectedCount() {
        if (typeof messageAreaItem != "undefined" && messageAreaItem != null) {
            return messageAreaItem.selectedCount;
        }
        return 0;
    } /*! end of selectedCount */

    /*! 返回当前已选中的项目的index数组。\note 它返回的数组是按照index值从小到大的顺序排列的。*/
    function selectedIndexes() {
        return privateData.selectedIndexes
    } /*! end of selectedIndexes */

    /*! 当列表的某一项被点击时触发， \a index 表示所点击的项目的索引值。*/
    signal delegateItemTriggered(int index)

    /*! 点击确认按钮后触发,  \a itemsIndex 为所有选中项目的index。 */
    signal notifySelectedItems(var itemsIndex)

    /*! 选中之后通知用户选中项目传出，并取消所有选中状态 */
    onAccepted:{
        notifySelectedItems(privateData.selectedIndexes)
        messageAreaItem.deselect()
    }
    /*! 设置某些项目为选中或未选中状态， \a indexArray 表示需要标记的项目索引值列表， \a selected 表示是否选中。 */
    function select(indexArray, selected) {
        if(itemCheckable) messageAreaItem.select(indexArray, selected)
    }

    /*! 取消选中所有已选中元素的选中状态。 */
    function deselect(){
        if(itemCheckable) messageAreaItem.deselect()
    }

    /*! 选中所有元素。 */
    function selectAll(){
        if(itemCheckable) messageAreaItem.selectAll()
    }

    /*! 对messageItem区域进行定制. */
    messageAreaLeftMargin: 0
    messageAreaRightMargin: 0

    /*! 通过计算得出选择框最大高度 */
    messageAreaComponent: CSelectListView{
        id: listView
        width: listDialog.width
        height: Math.min(listView.count, maxVisibleItems) * itemHeight
        clip: true
        model:listDialog.model
        exclusive: listDialog.itemExclusive
        interactive: listDialog.interactive
        reverseSelectOnExclusiveMode: listDialog.reverseSelectOnExclusiveMode
        delegate: itemDelegate
        selectable: itemCheckable
        CLine { width: parent.width - 140; anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter }
        onSelectedCountChanged: {
            privateData.selectedIndexes = listView.selectedIndexes
        }
        onSelectedIndexesChanged: {
            privateData.selectedIndexes = listView.selectedIndexes
        }
    }

    Component {
        id: myDelegate
        CSelectListViewDelegate{
            width: messageAreaItem.width; height: itemHeight; selectLabelRightMargin: 70

            Rectangle{
                color: enabled && pressed ? "#dddddd" : "transparent";
                anchors{ fill: parent; topMargin: -1; bottomMargin: -1 }
            }

            selectLabelComponent: listDialog.selectLabelComponent

            onClicked: {
                if(enabled){
                    /*! \internal 先保存index,待隐藏动画完成之后再发出triggered信号。*/
                    if(listDialog.itemExclusive){
                        privateData.lastTriggeredIndex = index;
                        listDialog.curIndex = index;
                       // hide();
                    }else{
                        delegateItemTriggered(index);
                    }
                }
            }

            Text{
                anchors { fill: parent; leftMargin: 70; rightMargin: 20 + 70 }
                elide: Text.ElideRight; verticalAlignment: Text.AlignVCenter
                font.pixelSize: itemFontSize; color: enabled ? itemTextColor : itemDisabledTextColor
                text: modelData
            }

            CLine{ width: parent.width - 140; anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter }

            enabled: privateData.enabled(index)
        }
    }

    QtObject {
        id: privateData
        property int lastTriggeredIndex: -1
        property var selectedIndexes: [-1]

        function enabled(index){
            return disabledIndexesArray.indexOf(index) === -1
        }
    }

    /*! \internal 当隐藏动画完成后，再发送triggered信号。 */
    onHideFinished: {
        if(itemExclusive && privateData.lastTriggeredIndex != -1){
            delegateItemTriggered(privateData.lastTriggeredIndex);
            privateData.lastTriggeredIndex = -1;
        }
    }

    /*! 列表对话框不可用项目数组 */
    property var disabledIndexesArray: [-1]

    /*! 项目文本颜色 */
    property color itemDisabledTextColor: "#CCCCCC"
}
