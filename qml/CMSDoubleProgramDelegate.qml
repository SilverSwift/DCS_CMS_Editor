import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ColumnLayout {

    Layout.margins: 10

    GroupBox{
        title: " CHAFF "
        Layout.fillWidth: true
        visible: fbq.visible || fbi.visible || fsq.visible || fsi.visible

        RowLayout{
            anchors.fill: parent
            Layout.alignment: Qt.AlignHCenter

            Item{Layout.preferredWidth: 5}

            CMSValueControl {
                id: fbq
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.chaffBrstQty["label"]
                value: model.chaffBrstQty["value"]
                visible: model.chaffBrstQty["isUsed"]

                onIncClicked: model.chaffBrstQty = +1
                onDecClicked: model.chaffBrstQty = -1
            }

            CMSValueControl {
                id: fbi
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.chaffBrstInrv["label"]
                value: model.chaffBrstInrv["value"]
                visible: model.chaffBrstInrv["isUsed"]

                onIncClicked: model.chaffBrstInrv = +1
                onDecClicked: model.chaffBrstInrv = -1
            }

            CMSValueControl {
                id: fsq
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.chaffSeqQty["label"]
                value: model.chaffSeqQty["value"]
                visible: model.chaffSeqQty["isUsed"]

                onIncClicked: model.chaffSeqQty = +1
                onDecClicked: model.chaffSeqQty = -1
            }
            CMSValueControl {
                id: fsi
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.chaffSeqInrv["label"]
                value: model.chaffSeqInrv["value"]
                visible: model.chaffSeqInrv["isUsed"]

                onIncClicked: model.chaffSeqInrv = +1
                onDecClicked: model.chaffSeqInrv = -1
            }


            Item{Layout.preferredWidth: 5}
        }

    }

    GroupBox{
        id: control
        title: " FLARE "
        Layout.fillWidth: true

        visible: cbq.visible || cbi.visible || csq.visible || csi.visible

        RowLayout{
            anchors.fill: parent
            Layout.alignment: Qt.AlignHCenter


            Item{Layout.preferredWidth: 5}

            CMSValueControl {
                id: cbq
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.flareBrstQty["label"]
                value: model.flareBrstQty["value"]
                visible: model.flareBrstQty["isUsed"]

                onIncClicked: model.flareBrstQty = +1
                onDecClicked: model.flareBrstQty = -1
            }

            CMSValueControl {
                id: cbi
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.flareBrstInrv["label"]
                value: model.flareBrstInrv["value"]
                visible: model.flareBrstInrv["isUsed"]

                onIncClicked: model.flareBrstInrv = +1
                onDecClicked: model.flareBrstInrv = -1
            }

            CMSValueControl {
                id: csq
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.flareSeqQty["label"]
                value: model.flareSeqQty["value"]
                visible: model.flareSeqQty["isUsed"]

                onIncClicked: model.flareSeqQty = +1
                onDecClicked: model.flareSeqQty = -1
            }
            CMSValueControl {
                id: csi
                Layout.fillWidth: true
                Layout.fillHeight: true

                label: model.flareSeqInrv["label"]
                value: model.flareSeqInrv["value"]
                visible: model.flareSeqInrv["isUsed"]

                onIncClicked: model.flareSeqInrv = +1
                onDecClicked: model.flareSeqInrv = -1
            }


            Item{Layout.preferredWidth: 5}
        }
    }

}
