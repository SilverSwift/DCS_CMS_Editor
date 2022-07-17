import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
Item{
    signal applyClicked()
    signal homeClicked()
    signal restoreClicked()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        Button{
            Layout.alignment: Qt.AlignRight
            icon.source: "qrc:/img/home.png"
            background: Rectangle{ color: "transparent" }
            onClicked: homeClicked()
        }

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

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            Button{
                text: qsTr("Apply")
                icon.source: "qrc:/img/apply.png"
                background: Rectangle{ color: "transparent" }
                onClicked: applyClicked()
            }
            Button{
                text: qsTr("Restore")
                icon.source: "qrc:/img/restore.png"
                background: Rectangle{ color: "transparent" }
                onClicked: restoreClicked()
            }
        }

        Item {
            Layout.preferredHeight: 10
        }

    }
}
