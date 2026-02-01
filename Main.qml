import QtQuick
import QtQuick.Controls
import "."
import QtQuick.Layouts

ApplicationWindow {
    width: 1000
    height: 600
    visible: true
    title: "Nightlock Bluet"
    readonly property int leftPanelWidth: 300

    Rectangle {
        id: background
        width: leftPanelWidth
        anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
        color: "#FFFFFF"

        Tree {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: menu.top
            }
        }

        // Меню снизу
        Rectangle {
            id: menu
            color: "white"
            width: parent.width
            height: 48
            anchors.bottom: parent.bottom

            Rectangle {
                width: parent.width
                height: 1
                anchors.top: parent.top
                color: "#E1E1E1"
            }
        }
    }











    Rectangle {
        id: primary
        anchors {
            left: background.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        // Левая граница
        Rectangle {
            id: leftBorder
            width: 3
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            color: "#E1E1E1"
        }

        ScrollView {
            id: scroll
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: leftBorder.right   // scroll начинается сразу после границы
                right: parent.right
            }
            clip: true

            // Overlay ScrollBar
            ScrollBar.vertical: ScrollBar {
                id: vbar
                parent: scroll
                anchors.right: scroll.right
                anchors.top: scroll.top
                anchors.bottom: scroll.bottom

                width: 6
                interactive: true
                policy: ScrollBar.AsNeeded
                opacity: (vbar.active || vbar.pressed) ? 0.6 : 0.0

                Behavior on opacity {
                    NumberAnimation { duration: 150 }
                }

                contentItem: Rectangle {
                    radius: 3
                    color: "black"
                }

                background: null
            }


            Column {
                id: contentColumn
                anchors.margins: 5
                width: scroll.availableWidth
                spacing: 2
                height: childrenRect.height   // вместо read-only implicitHeight

                Repeater {
                    model: 10
                    delegate: Rectangle {

                        width: contentColumn.width
                        height: 60  // чуть больше, чтобы уместить внутренние элементы
                        color: "red"
                        radius: 4

                        Row {
                            anchors.fill: parent
                            anchors.margins: 5
                            spacing: 5

                            // Левая квадратичная иконка
                            Rectangle {
                                width: 50
                                height: 50
                                color: "green"
                                radius: 10
                            }

                            Column {
                                spacing: 5

                                Rectangle {
                                    color: "green"
                                    width: 350
                                    height: 20

                                    Text {
                                        anchors.centerIn: parent
                                        text: "BSUIR IIS"
                                        color: "white"
                                    }
                                }

                                Rectangle {
                                    color: "blue"
                                    width: 350
                                    height: 20

                                    Text {
                                        anchors.centerIn: parent
                                        text: "BSUIR SEO"
                                        color: "white"
                                    }
                                }
                            }

                        }
                    }
                }




            }
        }
    }




















}
