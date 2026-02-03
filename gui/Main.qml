import QtQuick
import QtQuick.Controls
import "."
import QtQuick.Layouts

ApplicationWindow {
    width: 1000
    height: 600
    visible: true
    title: "Nightlock Bluet"

    readonly property int leftPanelWidth: 220
    readonly property int workspaceDefaultWidth: 300

    color: blue; // WARNING

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


Scroll {
    readonly property int workspaceDefaultWidth: 300
    id: primaryscroll
    width: workspaceDefaultWidth
    anchors {
        left: background.right
        top: parent.top
        bottom: parent.bottom
    }
}





Rectangle {
    anchors {
        top: parent.top
        left: primaryscroll.right
        right: parent.right
    }
    anchors.margins: 18
    // color: "red"
    color: "#FBFBFB"
    radius: 10

    height: contentColumn.implicitHeight + 35


    border.width: 1
    border.color: "#EFEFEF"

    Rectangle {

        anchors.fill: parent
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        anchors.topMargin: 12
        anchors.bottomMargin: 12
        // color: "green"
        color: "transparent"

        Column {
            id: contentColumn
            width: parent.width
            spacing: 6

            // Квадрат по центру
            Rectangle {
                width: 64
                height: 64
                color: "black"
                radius: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }

            // Подпись по центру
            Text {
                text: "Binance"
                font.bold: true
                font.pixelSize: 18
                anchors.horizontalCenter: parent.horizontalCenter
            }

            // Группа пользователь + пароль без spacing
            Column {
                width: parent.width
                spacing: 0  // вот тут убрали spacing между блоками

                Rectangle {
                    width: parent.width
                    height: 32
                    // color: "purple"
                    color: "transparent"
                    // полоска под блоком
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#EFEFEF"
                        anchors.bottom: parent.bottom
                    }
                    Text {
                        text: "Имя пользователя"
                        font.pixelSize: 16
                        anchors {
                            left: parent.left
                            leftMargin: 8
                            verticalCenter: parent.verticalCenter
                        }
                    }

                    Text {
                        text: "test@example.com"
                        color: "#A1A1A1"
                        font.pixelSize: 16
                        anchors {
                            right: parent.right
                            rightMargin: 8
                            verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 32
                    // color: "purple"
                    color: "transparent"

                    // полоска под блоком
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#EFEFEF"
                        anchors.bottom: parent.bottom

                    }

                    Text {
                        text: "Пароль"
                        font.pixelSize: 16
                        anchors {
                            left: parent.left
                            leftMargin: 8
                            verticalCenter: parent.verticalCenter
                        }
                    }

                    Text {
                        text: "*******"
                        color: "#A1A1A1"
                        font.pixelSize: 16
                        anchors {
                            right: parent.right
                            rightMargin: 8
                            verticalCenter: parent.verticalCenter
                        }
                    }

                }
            }
        }
    }
}







}
