import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: container
    color: "darkgray"
    border.color: "black"

    implicitHeight: layout.implicitHeight

    ColumnLayout {
        id: layout
        anchors.fill: parent

        Item{Layout.preferredHeight: 5}
        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 10
            Text {
                text: qsTr("Program name: ") + model.name + qsTr("\t\tComment: ")
                font.pointSize: 10
            }

            TextField {
                Layout.fillWidth: true
                text: model.comment
                placeholderText: qsTr("Type your comment here...")
                onEditingFinished: model.comment = text

            }
        }

        CMSSingleProgramDelegate{ visible: model.chaffIsSlave }
        CMSDoubleProgramDelegate{ visible: !model.chaffIsSlave }

        Item{Layout.preferredHeight: 5}
    }
}

