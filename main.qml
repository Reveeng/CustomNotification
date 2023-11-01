import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id:root
    width: 300
    height: 100
    visible:false
    property int notificationNumber : 0
    property int initialYPos: 0
    property int initialXPos:0
    y:initialYPos
    x:initialXPos-width-10
    property alias deviceName : nameText.text
    property alias connectionType: conText.text
    signal closed()
    onNotificationNumberChanged: {
        yAnim.from = root.y
        yAnim.to = initialYPos - (root.height+5)*notificationNumber
        yAnim.start()
    }
    onVisibleChanged: {
        if (root.visible)
            closeTimer.start()
    }
    Timer{
        id:closeTimer
        interval: 10000
        repeat:false
        onTriggered:{
            root.visible = false
            root.notificationNumber = 0
            root.y = initialYPos
        }
    }
    SmoothedAnimation{
        id:yAnim
        target:root
        property: "y"
        velocity: 200
        onFinished: {
            if (!root.visible)
                root.closed()
        }
    }
//    Behavior on y {SmoothedAnimation {
//            velocity: 200
//        }
//    }

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    Rectangle{
        id:title
        anchors.top:parent.top
        anchors.right:parent.right
        anchors.left:parent.left
        height:15
        color:Qt.darker("gray",2)
        Text{
            anchors.fill:parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 14
            text:"New device"
            color:"white"
        }
    }
    Item{
        anchors.top:title.bottom
        anchors.bottom: parent.bottom
        anchors.right:parent.right
        anchors.left:parent.left

        Text{
            id:nTxt
            anchors.top:parent.top
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            text:"Имя : "
        }
        Text{
            id:nameText
            anchors.verticalCenter: nTxt.verticalCenter
            anchors.left:nTxt.right
            anchors.leftMargin: 5
            anchors.right:parent.right
            anchors.rightMargin: 5
            wrapMode: Text.NoWrap
            elide:Text.ElideRight
        }
        MouseArea{
            id:ma
            hoverEnabled: true
            anchors.fill: nameText
            ToolTip.visible: ma.containsMouse
            ToolTip.text: nameText.text
        }
        Text{
            id:cTxt
            anchors.top:nTxt.bottom
            anchors.topMargin: 5
            anchors.left:parent.left
            anchors.leftMargin: 5
            text:"Подключение : "
        }
        Text{
            id:conText
            anchors.verticalCenter: cTxt.verticalCenter
            anchors.left:cTxt.right
            anchors.leftMargin: 5
        }

        Button{
            anchors.bottom: parent.bottom
            anchors.right:parent.right
            anchors.left:parent.left
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.bottomMargin: 5
            height:20
            text:"Взаимодействовать"
        }

    }
}
