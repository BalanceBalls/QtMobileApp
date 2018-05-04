import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import QtQml.Models 2.2
import QtGraphicalEffects 1.0

Window {

    id: mainwindow
    visible: true
    width: 360
    height: 520
    title: qsTr("Hello World")


    Drawer {
        id: sidepanel
        width: 280
        height: mainwindow.height
        dragMargin: 10
        dim: true

        Rectangle {
            id: rectangle
            x: 0
            y: 0
            z: -1
            width:  parent.width
            height: 170
            color: Material.color(Material.Indigo)

            Label{
                id: drawertext
                y: 21
                height: 17
                text: "Made by Tom cat"
                font.family: "Arial"
                font.pointSize: 16
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.bottom:  parent.bottom
                anchors.bottomMargin:  10
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: Material.color("#FFFFFF", 0)
            }
            Image {
                    id: img
                    source: "Graphics/tom.jpg"
                    property bool rounded: true
                    property bool adapt: true
                    width: 120
                    height: 120
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                    layer.enabled: rounded

                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: img.width
                            height: img.height
                            Rectangle {
                                color: "white"
                                anchors.centerIn: parent
                                width: img.adapt ? img.width : Math.min(img.width, img.height)
                                height: img.adapt ? img.height : width
                                radius: Math.min(width, height) + 50
                            }
                        }
                    }
            }
        }

    }

    ListView {
        id: listMain
        anchors.topMargin:  toolBar1.height
        anchors.fill: parent
        model: visualModel
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width

        DelegateModel {
                id: visualModel
                model: coin

                delegate: Rectangle {
                    id: rectangle1


                    width: listMain.width
                    height: 44

                    MouseArea {
                           anchors.fill: parent
                           onHoveredChanged: {parent.color = 'white'}
                           onHoverEnabledChanged: {parent.color = 'lightgrey'}

                       }
                    Text {
                        id: text2
                        text: symbol
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.topMargin: 0
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 10
                        anchors.left: rectangle1.left
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 14

                    }

                    Text {
                        id: text3
                        text: price
                        anchors.topMargin: 0
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.horizontalCenter: rectangle1.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 12
                    }

                    Text {
                        id: text4
                        text: if(percent24h > 0){
                                  "+" + percent24h + "%"
                            } else if(percent24h < 0){
                                  percent24h + "%"
                            }else {
                                  percent24h + "%"
                            }


                        anchors.topMargin: 0
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.right: rectangle1.right
                        anchors.rightMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 12
                        color: if(percent24h >= 0){
                                     Material.color(Material.Indigo)
                               } else if(percent24h < 0){
                                     Material.color(Material.Red)
                               }
                    }
                }
            }
    }

    ToolBar {
        id: toolBar1
        anchors.topMargin: 0
        font.pointSize: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
       // anchors.bottomMargin: listMain.top
        height: 60

        Rectangle {
            z: -1
            anchors.fill: parent
            color: Material.color(Material.Indigo)

        }
        Button{
            height: parent.height
            width: parent.height

            Rectangle{
                id: rectangle2
            height: parent.height
            width: parent.height

            color: Material.color(Material.Indigo)
                Image{
                   id: drawerImage
                   source: "Graphics/ic_menu_white_36dp.png"
                   property int size: 30  // default
                   //fillMode: Image.PreserveAspectCrop
                  anchors.fill: parent
                   MouseArea {
                          anchors.fill: parent
                          onClicked: sidepanel.open()

                      }

                }
           }
        }

        Popup {
                id: popupServerMsg
                x: 0
                y: 80
                width: mainwindow.width
                height: mainwindow.height - y*2 + 15

                modal: true
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent


                ListView{
                    id: jsonList
                    visible: true
                    anchors.horizontalCenter: parent.horizontalCenter

                    model: visualModelSer

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    DelegateModel {
                            id: visualModelSer
                            model: serverDataModel

                            delegate: Rectangle {
                                id: rectangle11
                                width: jsonList.width
                                height: 50

                               Column{
                                   id: columnList


                                   Row{

                                    Text{
                                        id: modelDateText
                                        text:"Date: " + model_date
                                        font.pixelSize: 12
                                        color: Material.color(Material.Indigo)

                                    }
                                    Text{
                                            id: modelTypeText
                                            text: " ,Type: " + Type
                                            font.pixelSize: 12
                                            color: Material.color(Material.Indigo)

                                    }
                                }
                                Row{

                                    Text{
                                        id: modelMarketText
                                        text:" Market: " + Market
                                        font.pixelSize: 12
                                        color: Material.color(Material.Indigo)

                                    }
                                    Text{
                                            id: modelPosText
                                            text: ", Pos: " + Pos
                                            font.pixelSize: 12
                                            color: Material.color(Material.Indigo)
                                    }
                                    Text{
                                        id: modelBidText
                                        text: " , Bid: " + Bid
                                        font.pixelSize: 12
                                        color: Material.color(Material.Indigo)
                                    }
                                }
                                Row{

                                    Text{
                                        id: modelCurRateText
                                        text: "Cur. rate: " + Cur_rate
                                        font.pixelSize: 12
                                        color: Material.color(Material.Indigo)
                                    }
                                    Text{
                                        id: modelTotalText
                                        text: " , Total: " + Total
                                        font.pixelSize: 12
                                        color: Material.color(Material.Indigo)
                                    }
                                }
                            }
                         }
                    }
                }
            }

       Button{
                height: parent.height
                width: parent.height
                anchors.right: parent.right

                Rectangle{
                    id: serverButton
                height: parent.height
                width: parent.height
                color: Material.color(Material.Indigo)
                    Image{
                       id: serBtnImg
                       source: "Graphics/ic_import_export_white_24dp.png"
                       property int size: 30  // default
                       //fillMode: Image.PreserveAspectCrop
                       anchors.fill: parent
                       MouseArea {
                              anchors.fill: parent
                              onClicked: {


                                  popupServerMsg.open()
                                  clientInstance.connectToServer()
                          }
                       }

                    }
               }
        }
        Text {
            id: text1
            color: "#ffffff"
            text: qsTr("Coinmarketcap")
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 96
            anchors.right: parent.right
            anchors.rightMargin: 95
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            font.pixelSize: 16
        }
    }
}
