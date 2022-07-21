import QtQuick 2.15
import QtQuick.Controls 2.15

Item{
    id: container
    property string text
    signal homeClicked()
    signal settingsClicked()

    implicitHeight: 50

    Component.onCompleted: state = "select"

    states: [
        State{
            name: "select"
            PropertyChanges{target: home; visible: false}
            PropertyChanges{target: label; text: qsTr("Select an aircraft to edit")}
            PropertyChanges{target: settings; visible: true}
        },
        State{
            name: "edit"
            PropertyChanges{target: home; visible: true}
            PropertyChanges{target: label; text: qsTr("Edit %1 aircraft").arg(container.text)}
            PropertyChanges{target: settings; visible: false}
        },
        State{
            name: "settings"
            PropertyChanges{target: home; visible: true}
            PropertyChanges{target: label; text: qsTr("Specify path to DCS root and saves")}
            PropertyChanges{target: settings; visible: false}
        }
    ]

    Button{
        id: home
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.top: parent.top
        implicitHeight: 50
        implicitWidth: 50
        icon.source: "qrc:/img/home.png"
        background: Rectangle{ color: "transparent" }
        ToolTip.visible: hovered
        ToolTip.delay: 1000
        ToolTip.text: qsTr("Back to main screen")

        onClicked: homeClicked()
    }

    Label{
        id: label
        anchors.bottom: parent.bottom
        anchors.verticalCenter: home.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Qt.AlignVCenter
    }

    Button{
        id: settings
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.top: parent.top
        implicitHeight: 50
        implicitWidth: 50
        icon.source: "qrc:/img/settings.png"
        background: Rectangle{ color: "transparent" }
        ToolTip.visible: hovered
        ToolTip.delay: 1000
        ToolTip.text: qsTr("Go to settings")

        onClicked: settingsClicked()

    }

}
