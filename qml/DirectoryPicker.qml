import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

GroupBox{
    id: box
    property string folder

    FolderDialog {
        id: dialog
        currentFolder: "file:///" + folder
        onAccepted: folder = label.text
    }

    RowLayout{
        id: row
        spacing: 10

        Label{
            id: label
            text: dialog.currentFolder.toString().substring(8)
            wrapMode: Text.WrapAnywhere
            Layout.preferredWidth: box.width - button.width - 3*row.spacing
            background: Rectangle{ color: "white" }
        }

        Button{
            id: button
            text: qsTr("Browse...")
            onClicked: dialog.open()
        }
    }
}
