import QtQuick 2.15
import QtQuick.Layouts 1.15

RowLayout{
    Layout.alignment: Qt.AlignHCenter
    Layout.fillWidth: true
    Layout.fillHeight: true

    Item{Layout.preferredWidth: 5}

    CMSValueControl {
        Layout.fillWidth: true
        Layout.fillHeight: true
        label: model.chaffBrstQty["label"]
        value: model.chaffBrstQty["value"]
        onIncClicked: model.chaffBrstQty = +1
        onDecClicked: model.chaffBrstQty = -1
        visible: model.chaffBrstQty["isUsed"]
    }

    CMSValueControl {
        Layout.fillWidth: true
        Layout.fillHeight: true
        label: model.flareBrstQty["label"]
        value: model.flareBrstQty["value"]
        visible: model.flareBrstQty["isUsed"]
        onIncClicked: model.flareBrstQty = +1
        onDecClicked: model.flareBrstQty = -1
    }

    CMSValueControl {
        Layout.fillWidth: true
        Layout.fillHeight: true
        label: model.flareBrstInrv["label"]
        value: model.flareBrstInrv["value"]
        visible: model.flareBrstInrv["isUsed"]
        onIncClicked: model.flareBrstInrv= +1
        onDecClicked: model.flareBrstInrv = -1
    }

    CMSValueControl {
        Layout.fillWidth: true
        Layout.fillHeight: true
        label: model.flareSeqInrv["label"]
        value: model.flareSeqInrv["value"]
        onIncClicked: model.flareSeqInrv = +1
        onDecClicked: model.flareSeqInrv = -1

    }

    CMSValueControl {
        Layout.fillWidth: true
        Layout.fillHeight: true
        label: model.flareSeqQty["label"]
        value: model.flareSeqQty["value"]
        onIncClicked: model.flareSeqQty = +1
        onDecClicked: model.flareSeqQty = -1
    }

    Item{Layout.preferredWidth: 5}
}


