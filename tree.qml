import QtQuick
import QtQuick.Controls
import Nightlock.Models 1.0

Item {
    id: root
    width: parent ? parent.width : 200
    height: parent ? parent.height : 300

    TreeView {
        id: tree
        anchors.fill: parent
        model: DirModel
        clip: true
        columnWidthProvider: function(column) { return root.width }

        property int selectedRow: -1

        delegate: TreeViewDelegate {
            contentItem: Text {
                text: model.display
                color: tree.selectedRow === row ? "white" : "black"
            }

            Rectangle {
                anchors.fill: parent
                color: tree.selectedRow === row
                    ? "black"
                    : (mouseArea.containsMouse ? "#F7F6F6" : "#FFFFFF")

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: tree.selectedRow = row
                }
            }
        }
    }
}
