import QtQuick 2.15
import QtQuick.Controls 2.15

MenuBar  {
    signal aboutTiggered()
    Menu {
        title: qsTr("&File")
        Action {
            text: qsTr("&Quit")
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: qsTr("&Help")
        Action {
            text: qsTr("&About")
            onTriggered: aboutTiggered()
        }
    }
}
