import QtQuick 2.2

MouseArea{
    id:delegateRoot
    /**
    @brief 表示当前是否可以滑动，通常与CSlideListView绑定
    */
    property bool slideable:true
    /**
    @brief 表示当前元素是否正处于滑动的状态，通常与CSlideListView的sliding绑定
    */
    readonly property alias sliding: privateData.dragMoving
    /**
    @brief 用于设置需要滑动的内容，使用CBaseSlideItem作为根目录，
                宽高与delegate等宽高，且不可以使用anchors进行布局。
    */
    property Item slideItem:Item{
        width: delegateRoot.width
        height: delegateRoot.height
        parent: delegateRoot
        z:delegateRoot.z + 10
        //color: delegateRoot.realPressed ? "lightgrey" : "white"

    }

    /**
    @brief 用于设定左侧菜单与slideItem之间的间隔
    */
    property int leftMenuOffset:0
    /**
    @brief 用于设定右侧菜单距离slideItem及滑动开时候右侧边缘之间的间隔
    */
    property int rightMenuOffset:0

    /**
    @brief 用于设置左侧滑动菜单
    */
    property Item _leftMenuItem :null
    /**
    @brief 用于设置右侧滑动菜单
    */
    property Item _rightMenuItem :Rectangle{
        width: 100
        height:delegateRoot.height
        color: "#5274B4"
        z:delegateRoot.z +1
        Text {
            id: name
            //anchors.centerIn: parent
            anchors.fill: parent
            text: qsTr("删除")
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                delegateRoot.rightMenuTriggered();
            }
        }
    }

    /**
    @brief 用于设定左侧拖动的最大距离，超过此距离时松
                开手会触发leftMenuTrigger信号，用户需要监听此信号完成快捷功能。
    */
    property int leftMenuMaximumX:240
    /**
    @brief 用于设定右侧菜单拖动的最小距离，超过此距离
                时在松开手的时候会自动滑开菜单。小于此值默认为取消打开快捷菜单的操作。
    */
    property int rightMenuMinimumX:100
    /**
    @brief 用于设定触发滑动效果的误差距离，
                当大于此值时认为用户需要的是滑动操作。
    */
    property int slideTriggerValue:10
    /**
    @brief 触发拖动最小的y方向间距
    */
    property int slideTriggerMaxYGap:10
    /**
    @brief 用于设定Delegate的背景，默认是有背景的，
                此不建议用户进行定制，除非有特别需求，默认为一个BorderImage
    */
//    property Item backgroundItem:BorderImage {
//        id: bgImgBorder
//        parent:delegateRoot        parent:delegateRoot
//        source:slideItem.x < -privateData.minUnit?"images/list-leftslide.png":(slideItem.x > privateData.minUnit?"images/list-rightslide.png":"images/listbg2.png")
//        z: - 1
//        anchors.fill: parent
//        border.left: 25; border.top: 15
//        border.right: 25; border.bottom: 15
//        visible: slideable &&(delegateRoot.pressed||(!delegateRoot.pressed && slideItem.x != 0))
//    }

    /**
    @param index:int 表示触发的元素序号
    @brief 当左侧菜单滑动超过触发条件时放开手会触发此信号，
                用户应该通过此信号完成相应的功能。
    */
    signal leftMenuTriggered(int index)
    signal rightMenuTriggered()

    signal slideFinished()

    property bool realPressed: false

    /**
    @brief
    */
    function clearTouchState() {
        privateData.dragMoving = false
    }
    /**
    @brief 初始滑动状态，当用户点击右侧菜单时，进行处理时应该调用此函数，以关闭当前状态
    */
    function toInitState(){
        drag.target = null
        if(slideItem.x != 0) {
            slideItemPA.to = 0
            slideItemPA.start()
//            delegateRoot.ListView.view.itemSlided = false
        }
    }

    drag.axis: Drag.XAxis
    //14.7.14
    drag.maximumX: 100
    drag.minimumX: _rightMenuItem?-width:0
    onPressed: {
        privateData.pressX = mouseX
        privateData.pressY = mouseY

        if(slideItemPA.running) { //for amiation mutex problem
            slideItemPA.stop()
        }
        realPressedTimer.start()
        //notify the other list items to set to default state
//        ListView.view.curPressedItemChanged(index)
    }
    Timer{
        id:realPressedTimer
        interval: 50
        onTriggered: {
            if(Math.abs(privateData.pressX - delegateRoot.mouseX) < 1 )
                delegateRoot.realPressed = true
        }

    }

    onMouseXChanged:{
//        if(delegateRoot.ListView.view.__occupiedIndex >= 0 && index !== delegateRoot.ListView.view.__occupiedIndex)
//            return
        if( !slideable || Math.floor(mouseX)==Math.floor(privateData.pressX))
            return
        if(!privateData.dragMoving) {
            if(drag.target ||  (Math.abs(mouseX-privateData.pressX) > slideTriggerValue && Math.abs(mouseY - privateData.pressY) < slideTriggerMaxYGap &&(_leftMenuItem || _rightMenuItem)) ){
               privateData.dragMoving = true
            }
        }
    }
    onReleased: {
        console.log("rererereressssssssssssssss")
        slideFinished();
        privateData.releaseX = mouseX
        clearTouchState()
    }
    onCanceled: {
        privateData.releaseX = privateData.pressX
        clearTouchState()
        delegateRoot.realPressed = false
    }
    onClicked: {
//        if(delegateRoot.ListView.view.__occupiedIndex == index) {
//            toInitState()
//        } else if(delegateRoot.ListView.view.__occupiedIndex==-1&&privateData.canTrigger) {
//            triggered(delegateRoot)
//        } else{
//            delegateRoot.ListView.view.resetItemState()
//        }
    }
    onSlidingChanged:   {
//        delegateRoot.ListView.view.itemSliding = sliding

        if(privateData.dragMoving) {
            if(!drag.target) {
                if(_leftMenuItem) {
                    _leftMenuItem.parent = delegateRoot
                    _leftMenuItem.z = 100
                    _leftMenuItem.x = slideItem.x-_leftMenuItem.width-leftMenuOffset
                    _leftMenuItem.anchors.verticalCenter = _leftMenuItem.parent.verticalCenter
                    _leftMenuItem.visible = true
                }
                if(_rightMenuItem) {
                    _rightMenuItem.parent = delegateRoot
                    _rightMenuItem.anchors.verticalCenter = _rightMenuItem.parent.verticalCenter
                    _rightMenuItem.z = 100
                    _rightMenuItem.x = slideItem.x+slideItem.width+rightMenuOffset
                    _rightMenuItem.visible = true
                }

                drag.target = slideItem
//                delegateRoot.ListView.view.__occupiedIndex = index
//                delegateRoot.ListView.view.__slideDelegateItem = delegateRoot
            }
        } else {
            if(_leftMenuItem && slideItem.x > 0) {
                if(slideItem.x >= leftMenuMaximumX)
                    privateData.sendLeftMenuTriggeredFlag = true
                drag.target = null
                slideItemPA.to = 0
                slideItemPA.start()
            } else if(_rightMenuItem && slideItem.x < 0 ) {
                if(slideItem.x > -slideTriggerValue || ( privateData.pressX - privateData.releaseX < -privateData.valueOfTriggerWhenRelease)) {
                    drag.target = null
                    slideItemPA.to = 0
                    slideItemPA.start()
                } else{
                    var finalOffset = Math.max(-_rightMenuItem.width-rightMenuOffset*2, -(delegateRoot.width-rightMenuMinimumX))
                    slideItemPA.to = finalOffset
                    slideItemPA.start()
//                    delegateRoot.ListView.view.itemSlided = true
                }
            } else{
                drag.target = null
                slideItemPA.to = 0
                slideItemPA.start()
//                delegateRoot.ListView.view.itemSlided = false
//                delegateRoot.ListView.view.__occupiedIndex = -1
//                delegateRoot.ListView.view.__slideDelegateItem = null
            }
        }
    }

//    Binding{
//        target:delegateRoot
//        property:"slideable"
//        value:(delegateRoot.ListView.view.slideable)
//    }
    PropertyAnimation{
        id:slideItemPA
        target:slideItem
        property:"x"
        duration: 100
        onStopped: {
            if(Math.floor(slideItem.x) == 0) {
                if(_leftMenuItem&&_leftMenuItem.parent == delegateRoot)
                    _leftMenuItem.visible = false
                if(_rightMenuItem&&_rightMenuItem.parent == delegateRoot)
                    _rightMenuItem.visible = false
                if(privateData.sendLeftMenuTriggeredFlag)
                {
                    leftTriggerTimer.restart()
                    privateData.sendLeftMenuTriggeredFlag = false
                }
//                delegateRoot.ListView.view.itemSlided = false
//                delegateRoot.ListView.view.__occupiedIndex = -1
//                delegateRoot.ListView.view.__slideDelegateItem = null
            } else {
//                delegateRoot.ListView.view.itemSlided = true
            }
        }
    }
    Timer{
        id:leftTriggerTimer
        running: false
        repeat: false
        interval: 20
        onTriggered: {
            delegateRoot.leftMenuTriggered(index)
        }
    }
    /**
    @brief slideIem的背景，用于体现滑动状态时的状态
    */
//    Connections{
//        target: delegateRoot.ListView.view
//        onCurPressedItemChanged:{
//            if(delegateRoot.ListView.view.__occupiedIndex >=0 ) {
//                privateData.canTrigger = false
//            } else {
//                privateData.canTrigger = true
//            }

//            if(curIndex != index&&slideItem.x != 0) {
//                slideItemPA.running = false
//                toInitState()
//            }
//        }
//        onResetItemState:{
//            if(slideItem.x != 0) {
//                slideItemPA.running = false
//                toInitState()
//            }
//        }
//    }
    Connections{
        target:slideItem

        onXChanged: {
            if(delegateRoot._leftMenuItem && slideItem.x < leftMenuMaximumX){
                delegateRoot._leftMenuItem.x = slideItem.x-delegateRoot._leftMenuItem.width-delegateRoot.leftMenuOffset
            }
            if(_rightMenuItem) {
                var finalOffset = delegateRoot.width - _rightMenuItem.width - rightMenuOffset
                var newX = Math.max(finalOffset, slideItem.x+slideItem.width+rightMenuOffset)
                delegateRoot._rightMenuItem.x = newX
                delegateRoot._rightMenuItem.visible = true
            }
        }
    }

    Component.onCompleted: {
//        if(slideItem) {
//            slideItem.parent = delegateRoot
//            slideItem.width = Qt.binding(function(){return delegateRoot.width})
//            slideItem.height = Qt.binding(function(){return delegateRoot.height})
//        }
//        if(!_leftMenuItem){
//            _leftMenuItem = ListView.view.leftMenuItem
//        }
//        if(!_rightMenuItem){
//            _rightMenuItem = ListView.view.rightMenuItem
//        }
    }
    Component.onDestruction: {
//        if(delegateRoot.ListView.view && index == delegateRoot.ListView.view.__occupiedIndex) {
//            delegateRoot.ListView.view.itemSlided = false
//            delegateRoot.ListView.view.__occupiedIndex = -1
//            delegateRoot.ListView.view.__slideDelegateItem = null
//        }
    }

    QtObject{
        id: privateData

        property int minUnit:10
        property bool canTrigger:true
        property real pressX:0
        property real pressY:0
        property real releaseX:0
        property real valueOfTriggerWhenRelease:100
        property bool dragMoving:false
        property bool sendLeftMenuTriggeredFlag:false
    }
}
