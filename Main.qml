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
    readonly property int workspaceDefaultWidth: 300

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
        // width: 300
        anchors {
            left: background.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        // Левая граница
        Rectangle {
            id: leftBorder
            width: 1
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

                // width: 300

                id: contentColumn
                anchors.margins: 5
                width: scroll.availableWidth
                spacing: 5 // отсуп между блоками
                height: childrenRect.height   // вместо read-only implicitHeight

                Repeater {
                    model: 100
                    delegate: Rectangle {

                        width: contentColumn.width
                        // width: 300  // фиксированная ширина
                        // anchors.horizontalCenter: parent.horizontalCenter
                        height: 53  // чуть больше, чтобы уместить внутренние элементы
                        // color: "red" // DEBUG COLOR
                        radius: 4
                        // боковые отступы
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        anchors.topMargin: 5
                        anchors.bottomMargin: 5

                        // полоски
                        Rectangle {
                            anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
                            height: 1
                            color: "#E1E1E1"
                        }

                        Row {
                            anchors.fill: parent
                            anchors.margins: 7.5 // отсуп красного
                            spacing: 5 // отсуп текстов от логотипа

                            // Левая квадратичная иконка
                            Rectangle {
                                width: 37
                                height: 37
                                color: "black"
                                radius: 10
                            }

                            Column {
                                spacing: 4

                                Rectangle {
                                    // color: "green"
                                    width: 150
                                    height: 15

                                    Text {
                                        anchors.fill: parent   // текст занимает весь Rectangle
                                        text: "IIS BSUIR"
                                        color: "black"
                                        horizontalAlignment: Text.AlignLeft   // выравнивание по левому краю
                                        verticalAlignment: Text.AlignVCenter // по вертикали по центру
                                        leftPadding: 10
                                        font.pixelSize: 14
                                        font.bold: true
                                    }
                                }

                                Rectangle {
                                    // color: "blue"
                                    width: 150
                                    height: 15

                                    Text {
                                        anchors.fill: parent   // текст занимает весь Rectangle
                                        text: "rodukov138@icloud.com"
                                        color: "#767676"
                                        horizontalAlignment: Text.AlignLeft   // выравнивание по левому краю
                                        verticalAlignment: Text.AlignVCenter // по вертикали по центру
                                        leftPadding: 10
                                        font.pixelSize: 12

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
