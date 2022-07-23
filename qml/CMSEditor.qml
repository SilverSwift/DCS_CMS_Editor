import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item{
    signal applyClicked()
    signal completed()
    signal resetClicked()
    signal restoreClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true
            ListView{
                id: view
                anchors.fill: parent
                anchors.margins: 5
                model: app_instance.model
                spacing: 5
                delegate: CMSProgramDelegate { width: view.width}
            }
        }
        Item{ Layout.preferredHeight: 10 }

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            Button{
                text: qsTr("Apply")
                icon.source: "qrc:/img/apply.png"
                background: Rectangle{ color: "transparent" }
                ToolTip.visible: hovered
                ToolTip.delay: 1000
                ToolTip.text: qsTr("Write current setup to DCS")

                onClicked: applyClicked()
            }

            Button{
                text: qsTr("Reset")
                icon.source: "qrc:/img/reset.png"
                background: Rectangle{ color: "transparent" }
                ToolTip.visible: hovered
                ToolTip.delay: 1000
                ToolTip.text: qsTr("Reset DCS settings to defaults")

                onClicked: resetClicked()
            }

            Button{
                text: qsTr("Restore")
                icon.source: "qrc:/img/restore.png"
                background: Rectangle{ color: "transparent" }
                ToolTip.visible: hovered
                ToolTip.delay: 1000
                ToolTip.text: qsTr("Restore DCS settings from backup")

                onClicked: restoreClicked()
            }
        }

        Item {
            Layout.preferredHeight: 10
        }

    }
}
