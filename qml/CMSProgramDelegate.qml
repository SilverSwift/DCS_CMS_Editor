import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    color: "darkgray"
    border.color: "black"

    implicitHeight: layout.implicitHeight

    ColumnLayout {
        id: layout
        anchors.fill: parent

        Item{Layout.preferredHeight: 5}

        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "\t\t\tprogram: "+ model.name + "\t" + model.comment
        }

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            Item{Layout.preferredWidth: 5}

            CMSValueControl {
                Layout.fillWidth: true
                Layout.fillHeight: true
                label: "CHAFF"
                value: model.chaff
                onIncClicked: model.chaffinc = 1
                onDecClicked: model.chaffdec = 1
            }

            CMSValueControl {
                Layout.fillWidth: true
                Layout.fillHeight: true
                label: "FLARE"
                value: model.flare
                onIncClicked: model.flareinc = 1
                onDecClicked: model.flaredec = 1
            }

            CMSValueControl {
                Layout.fillWidth: true
                Layout.fillHeight: true
                label: "INTRV"
                value: model.intv
                onIncClicked: model.intvinc = 1
                onDecClicked: model.intvdec = 1
            }

            CMSValueControl {
                Layout.fillWidth: true
                Layout.fillHeight: true
                label: "CYCLE"
                value: model.cycle
                onIncClicked: model.cycleinc = 1
                onDecClicked: model.cycledec = 1
            }
            Item{Layout.preferredWidth: 5}
        }

        Item{Layout.preferredHeight: 5}
    }
}

