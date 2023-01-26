import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls

Window {
    id :root
    width: 600
    height: 520
    visible: true
   // color: "black"
    title: qsTr("dd")
    Image {
      //  width: 600
      //  height: 520
        id: backgroundimage
        x: -21
        y: -10
        width: 621
        height: 530
        //anchors.fill: root
        source: "dashBackground.jpg"
    }




StackView
{
    id:id_stack
    x: -21
    y: -10
    // anchors.fill:parent
    anchors.leftMargin: -21
    anchors.topMargin: -15
    anchors.rightMargin: 0
    anchors.bottomMargin: 0
    width: 621
    height: 530
//initialItem: Qt.resolvedUrl("qrc:/DataDisplay.qml")

            Rectangle {
            id:childWindow
            width: 184
            height: 316
            x:217
            y:107
            // color: "chartreuse"
            border.width: 5
            border.color: "blue"
            radius: 260
            Text {
                id: id_start
                font.bold: true
                font.pixelSize:  40
                text: "START"
                anchors.centerIn: parent

            }
            gradient: Gradient {
                  GradientStop { position: 0.0; color: "red" }
                  GradientStop { position: 0.33; color: "yellow" }
                  GradientStop { position: 1.0; color: "green" }
              }

           MouseArea{
               anchors.fill: parent
               anchors.rightMargin: -5
               anchors.bottomMargin: 0
               anchors.leftMargin: -5
               anchors.topMargin: 0
               onClicked:{
              id_stack.replace("DataDisplay.qml")
              mainAccess.mainclikedbuttonTIMERSSTARTING()
           }


           }


    }
}




}
