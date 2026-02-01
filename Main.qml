import QtQuick
import QtQuick.Controls
import Nightlock.Models 1.0

ApplicationWindow {
    width: 1000
    height: 600
    visible: true
    title: "Nightlock Bluet"
    readonly property int leftPanelWidth: 350

    Rectangle {
        id: background
        width: leftPanelWidth
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
        color: "#FFFFFF"


        /*
        Rectangle {
            id: great_button
            width: parent.width
            height: 100
            color: "green"
            anchors.top: parent.top
        } */


        TreeView {
            id: tree
            anchors {
                 top: parent.top // great_button
                 left: parent.left
                 right: parent.right
                 bottom: parent.bottom
             }
            model: DirModel
            clip: true
            columnWidthProvider: function(column) { return background.width }

            property int selectedRow: -1  // индекс выделенной строки


            delegate: TreeViewDelegate {

                contentItem: Text {
                    text: model.display
                    color: tree.selectedRow === row
                        ? "white"
                        : "black"
                }

                Rectangle {
                    anchors.fill: parent
                    color: tree.selectedRow === row
                        ? "black"                     // выделенная строка
                        : (mouseArea.containsMouse ? "#F7F6F6" : "#FFFFFF") // hover

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            tree.selectedRow = row  // меняем выделение на текущую строку
                        }
                    }
                }
            }


        }



    }

    Rectangle {
        id: primary
        anchors { left: background.right; right: parent.right; top: parent.top; bottom: parent.bottom }
        color: "#F7F6F6"

        // Правая граница
        Rectangle {
            width: 1
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            color: "#E1E1E1"
        }

    }
}
