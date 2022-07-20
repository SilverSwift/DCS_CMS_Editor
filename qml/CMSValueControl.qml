import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: control
    signal incClicked()
    signal decClicked()

    property string label: "unnamed"
    property string value: "0"

    spacing: 0

    FontLoader{
        id: fontLoader
        source: "qrc:/fonts/digital-7 (mono).ttf"
    }

    Label{
        Layout.fillWidth: true
        Layout.fillHeight: true
        horizontalAlignment: Qt.AlignHCenter
        text: label + " " + value
        verticalAlignment: Qt.AlignVCenter
        font.pointSize: 14
        font.family: fontLoader.name
        font.bold: true
        color: "black"
        background: Rectangle{color: "white"}
        clip: true
    }

    ColumnLayout{
        spacing: 0
        Layout.fillHeight: true
        Layout.fillWidth: true

        Button{
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            background: Rectangle{ color: "white" }
            autoRepeat: true
            icon.source: "qrc:/img/up.png"
            onClicked: control.incClicked()
        }

        Button{
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            background: Rectangle{ color: "white" }
            autoRepeat: true
            icon.source: "qrc:/img/down.png"
            onClicked: control.decClicked()
        }
    }
}
