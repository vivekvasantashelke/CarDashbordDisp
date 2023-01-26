import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle{
id:statusBar
height: 40
anchors{
left: parent.left
top:parent.top
right: parent.right
}

color: Qt.rgba(0,0,0,0)

Text{

id:statusBartemptime
anchors{
top: parent.top
right: parent.right
rightMargin: 1
}
height: parent.height
width: parent.width/4
verticalAlignment: Text.AlignVCenter
font.pixelSize: 20

color: "white"
text: "21 F 12:55 AM"
}
}
