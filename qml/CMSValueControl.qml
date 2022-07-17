import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: control
    signal incClicked()
    signal decClicked()
    property string label: "unnamed"
    property string value: "0"

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
        color: "#442233"
        background: Rectangle{color:"#99225522"}
        clip: true
    }

    ColumnLayout{
        spacing: 0
        Layout.fillHeight: true
        Layout.fillWidth: true
        Button{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 30

            autoRepeat: true
            text: "+"
            onClicked: control.incClicked()
        }

        Button{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 30

            autoRepeat: true
            text: "-"
            onClicked: control.decClicked()
        }
    }
}
