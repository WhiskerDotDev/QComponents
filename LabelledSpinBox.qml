import QtQuick;
import QComponents;

Column{
      id: root_column;
      property int labelHeight: Math.round(this.height/2);
      antialiasing: false; smooth: false;


      Text{
            id: m_label;
            height: root_column.labelHeight; width: root_column.width;
            verticalAlignment: Text.AlignVCenter;
            visible: true; antialiasing: root_column.antialiasing; smooth: root_column.smooth;
            wrapMode: Text.NoWrap;
            textFormat: Text.PlainText;
            color: "#000000";
            minimumPixelSize: 1;
            fontSizeMode: Text.Fit;
            z: root_column.z;
      } property alias label: m_label;

      SimpleSpinBox{
            id: m_spinbox;
            height: root_column.height - root_column.labelHeight;
            width: root_column.width;
            z: root_column.z;
      } property alias spinbox: m_spinbox


}